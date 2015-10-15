//
//  mapmatching.cpp
//  
//
//  Created by XoX on 15/10/3.
//
//

#include "stdafx.h"
#include "Point.h"
#include "basis.h"

extern Grid *grids;
extern Edge *edges;
extern Point *vertices;
extern int rows;
extern int columns;

int NumofCadt = 10;

//parameters used in score computing
const double ud = 10;
const double a = 0.17;
const double nd = 1.4;
const double ua = 10;
const double na = 4;
const double multipler = 20;
const double para1 = 0.5;
const double para2 = 1 - para1;
const double threshold = 50;

void    ReadTrajectory(std::string filename, std::vector <Point> &traj)
{
    FILE *fp;
    fp = fopen(filename.c_str(), "r");
    double lat, lng, time;
    int i = 0;
    
    while (fscanf(fp, "%lf %lf %lf\n", &lat, &lng, &time) != EOF)
    {
        Point pt(lat,lng);
        //DisplayAPoint(pt);
        traj.push_back(pt);
        i++;
    }
    printf("trajectory size : %d\n", i);
    traj.resize(i);
    //DisplayAPoint(pt);
    //DisplayAPoint(traj[0]);
}
//write matched trajectory
void    WriteMatchedTrajectory(std::string filename, std::vector <int> mapped_edge, std::vector <Point> mapped_traj)
{
    FILE *fpedge, *fptraj;
    //fp = fopen(filename.c_str(), "w");
    printf("%s\n", filename.c_str());
    int length = filename.length();
    std::string name, filetraj, fileedge;
    int pos;
    Point pttemp;
    double lat, lng;
    
    pos = filename.find_last_of("/\\");
    //printf("%d\n", pos);
    pos++;
    name = filename.substr(pos, length-pos);
    
    filetraj = "./matched/" + name + "_traj.txt";
    fileedge = "./matched/" + name + "_edge.txt";
    
    fpedge = fopen(fileedge.c_str(), "w");
    fptraj = fopen(filetraj.c_str(), "w");
    //fp = fopen(name.c_str(), "w");
    //printf("%s\n", name.c_str());
    
    //write edges & traj points
    for (int i = 0; i < mapped_edge.size(); i++)
    {
        pttemp = mapped_traj[i];
        lat = pttemp.getLat();
        lng = pttemp.getLon();
        if (mapped_edge[i] == 0)
        {
            lat = lng = 0;
        }
        //if (mapped_edge[i] != 0)
        //{
            fprintf(fpedge, "%d\n", mapped_edge[i]);
            fprintf(fptraj, "%lf %lf\n", lat, lng);
        //}
    }
    
    fclose(fpedge);
    fclose(fptraj);
}
//map a trajectory
void    MapTrajectory(std::vector <Point> traj, std::string filename)
{
    //printf("map function\n");
    int size = traj.size();
    std::vector <Point> mapped_traj(size);
    std::vector <int> mapped_edge(size);
    Point mapped_point;
    Point nomatched(0,0);
    double score, maxscore;
    int lastedgeindex = 0, edgeindex = 0;
    bool matched = false;
    
    
    std::vector <int> cadtGrid, cadtEdge;
    
    //double dist =
    
    for (int i = 0; i < size; i++)
    {
        //printf("point id of the trajectory: %d\n", i);
        DisplayAPoint(traj[i]);
        GetCandidateGrid(traj[i], cadtGrid);
        GetCandidateEdge(traj[i], cadtGrid, cadtEdge);
        maxscore = 0;
        lastedgeindex = edgeindex;
        edgeindex = 0;
        
        if (cadtEdge.size() == 0)
        {
            mapped_edge.push_back(0);
            mapped_traj.push_back(nomatched);
        }
        else
        {
            matched = true;
            std::cout << "find the max score" << std::endl;
            for(int k = 0; k < cadtEdge.size(); k++)
            {
                std::cout << cadtEdge[k] << std::endl;
                if (i == 0)
                    score = partscore(traj[i], traj[i], edges[cadtEdge[k]], true);
                else
                    score = partscore(traj[i-1], traj[i], edges[cadtEdge[k]], false);
                
                std::cout << "score : " << score << " maxscore : " << maxscore << std::endl;
             
                if(score > maxscore)
                {
                    std::cout << "score : " << score << " maxscore : " << maxscore << std::endl;
                    maxscore = score;
                    edgeindex = cadtEdge[k];
                }
                std::cout << "most suitable edge now" << std::endl;
                std::cout << edgeindex << std::endl;
            }
            std::cout << "************************************************************************" << std::endl;
            std::cout << "*********************************** " << i <<"*************************************" << std::endl;
            
            /*add a threshold*/

            mapped_edge.push_back(edgeindex);
//            if(maxscore > 0)
//            {
                std::cout << "mapped edge" << std::endl;
                DisplayAnEdge(edges[edgeindex]);
                mapped_point = pToseg(traj[i], edges[edgeindex].start, edges[edgeindex].end);
                std::cout << ">>>>>>>>>>>>>>point in the trajectory" << std::endl;
                DisplayAPoint(traj[i]);
                std::cout << ">>>>>>>>>>>>>>edge start point" << std::endl;
                DisplayAPoint(edges[edgeindex].start);
                std::cout << ">>>>>>>>>>>>>>point latitude" << edges[edgeindex].start.getLat() << std::endl;
                std::cout << ">>>>>>>>>>>>>>point longmitude" << edges[edgeindex].start.getLon() << std::endl;
                std::cout << ">>>>>>>>>>>>>>edge end point" << std::endl;
                DisplayAPoint(edges[edgeindex].end);
                std::cout << ">>>>>>>>>>>>>>mapped point" << std::endl;
                DisplayAPoint(mapped_point);
                mapped_traj.push_back(mapped_point);
                std::cout << "************************************************************************" << std::endl;
//            }
//            else
//            {
//                std::cout << "no matched edge" << std::endl;
//                mapped_point = nomatched;
//                mapped_traj.push_back(mapped_point);
//                matched = false;
//            }

        }
        cadtGrid.clear();
        cadtEdge.clear();
    }
    
    if (matched)
    {
        printf("Matching succeed!\n");
        WriteMatchedTrajectory(filename, mapped_edge, mapped_traj);
    }
    else
        printf("Matching Failed!\n");
    
}
//get all the candidate grids
void    GetCandidateGrid(Point pt, std::vector <int> &cadtGrid)
{
    Grid center = grids[pt.gid];
    //printf("grid id: %d\n", pt.gid);
    bool flag[4];
    double dist[4]; //0:up, 1:right, 2:down, 3:left
    int tempindex[4] = {pt.gid+columns, pt.gid+1, pt.gid-columns, pt.gid-1};
    cadtGrid.push_back(pt.gid);
    
    //distance to the four lines of the grid
    dist[0] = dispToseg(pt, center.corner[0], center.corner[1]);
    dist[1] = dispToseg(pt, center.corner[1], center.corner[2]);
    dist[2] = dispToseg(pt, center.corner[2], center.corner[3]);
    dist[3] = dispToseg(pt, center.corner[3], center.corner[0]);
    
    
    std::cout << "grid height is " << dispToseg(center.corner[2], center.corner[0], center.corner[1]) << std::endl;
    std::cout << "grid width is " << dispToseg(center.corner[2], center.corner[0], center.corner[3]) << std::endl;
    /*
    DisplayAPoint(center.corner[0]);
    DisplayAPoint(center.corner[1]);
    DisplayAPoint(center.corner[2]);
    DisplayAPoint(center.corner[3]);
    */
    //if the distance is smaller than 100 meters, then set the flag true;
    for (int i = 0; i < 4; i++)
    {
        printf("%d: %lf\n", i, dist[i]);
        if (dist[i] < 100)
        {
            flag[i] = true;
            cadtGrid.push_back(tempindex[i]);
        }
        else
            flag[i] = false;
    }
    
    //get all the index of the candidate grids
    if(flag[0]&&flag[1])
        cadtGrid.push_back(pt.gid+columns+1);
    else
        if(flag[1]&&flag[2])
            cadtGrid.push_back(pt.gid-columns+1);
        else
            if(flag[2]&&flag[3])
                cadtGrid.push_back(pt.gid-columns-1);
            else
                if(flag[3]&&flag[1])
                    cadtGrid.push_back(pt.gid+columns-1);
    cadtGrid.resize(cadtGrid.size());
}
//get all candidate edge id, according to the distance.
void    GetCandidateEdge(Point pt, std::vector <int> &cadtGrid, std::vector <int> &cadtEdge)
{
    //use set in order to avoid some edges contained by more than one grid.
    std::set <int> AllCandidate;
    std::priority_queue < std::pair <double, int> > Q;
    int gridid, eid;
    double dist;
    int size;
    
    std::cout << "there are " << cadtGrid.size() << " candidate grids" << std::endl;
    for (int i = 0; i < cadtGrid.size(); i++)
    {
        gridid = cadtGrid[i];
        std::cout << gridid << std::endl;
        //DisplayAGrid(grids[gridid]);
        AllCandidate.insert(grids[gridid].eids.begin(), grids[gridid].eids.end());
    }
    std::cout << "There are " << AllCandidate.size() << " candidate edges" << std::endl;
    
    if(AllCandidate.size() == 0)
        return;
    dist = dispToseg(pt, edges[273467].start, edges[273467].end);
    std::cout << "distance to the first edge 273467: " << std::endl;
    std::cout << "----------------" << dist << "----------------" << std::endl;
    
    for (std::set <int>::iterator it = AllCandidate.begin(); it != AllCandidate.end(); it++)
    {
        eid = *it;
        dist = dispToseg(pt, edges[eid].start, edges[eid].end);
        if (dist < 100)
            Q.push(std::make_pair(dist, eid));
        
        if (Q.size() > NumofCadt)
            Q.pop();
    }
    
    size = Q.size();
    std::cout << "cadt edges in priority queue" << std::endl;
    for (int i = 0; i < size; i++)
    {
        
        std::cout << Q.top().second << " " << Q.top().first << std::endl;
        cadtEdge.push_back(Q.top().second);
        Q.pop();
    }
}
// get part score of two points and one candidate edge;
double  partscore(Point pi, Point pj, Edge edge, bool flag)
{
    double sa, sd;
    double CosofAngle;
    double dist;
    Point VecofPoint, VecofEdge;
    
    dist = dispToseg(pj, edge.start, edge.end);
    
    
    //sd = ud - a / pow(dist, nd);
    sd = para1 * multipler * 1/dist;
    std::cout << "distance :" << dist << std::endl;
    std::cout << "distance score : " << sd << std::endl;
    
    /**added 10.13 set a distance threshold**/
//    if (dist > 100)
//    {
//        return -1;
//    }
    
    /**/
    if (flag)
        return sd;
    
    VecofPoint = pj - pi;
    VecofEdge = edge.end - edge.start;
    CosofAngle = VecofEdge * VecofPoint/(VecofPoint.length() * VecofEdge.length());
    CosofAngle = fabs(CosofAngle);
    
    //sa = ua*pow(CosofAngle, na);
    sa = para2 * CosofAngle;
    std::cout << "angle score : " << sa << std::endl;

    return sa+sd;
}
/*
double GetScore(int i)
{
    Point pi = traj[i];
    Point pj = traj[i+1];
    double score;
    double maxscore = 0;
    int bound;
    
    std::vector <int> cadtGrid, cadtEdge;
    GetCandidateGrid(pi, cadtGrid);
    GetCandidateEdge(pi, cadtGrid, cadtEdge);
    
    
    if (i == traj.size()-2)
    {
        for (int k = 0; k < cadtEdge.size(); k++)
        {
            score = partscore(pi, pj, edges[cadtEdge[k]]);
            if (maxscore < score)
            {
                maxscore = score;
            }
        }
        return maxscore;
    }
    else
    {
        if ((i+5) < traj.size())
            bound = i+5;
        else
            bound = traj.size();
        for (int m = i; m < bound; m++)
        {
            for (int k = 0; k < cadtEdge.size(); k++)
            {
                score  = GetScore(i)
            }
        }
       
    }

}
void GetBestMatching(int i, int size)
{
    std::vector <int> cadtGrid, cadtEdge;
    int bound;
    double score;
    
    GetCandidateGrid(traj[0], cadtGrid);
    GetCandidateEdge(traj[0], cadtGrid, cadtEdge);
    
    if ((i+5) < size)
        bound = i+5;
    else
        bound = size;
    
    for (int j = 0; j < cadtEdge.size(); j++)
    {
        for (int k = i+1; k < bound; k++)
        {
            score += GetScore(p)
        }
    }
    
    


}
*/