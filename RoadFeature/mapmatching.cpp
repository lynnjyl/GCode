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
extern POINT *vertices;
extern int rows;
extern int columns;

int NumofCadt = 10;

void ReadTrajectory(std::string filename, std::vector <Point> &traj)
{
    FILE *fp;
    fp = fopen(filename.c_str(), "r+");
    double lat, lng, time;
    int i = 0;
    
    while (fscanf(fp, "%lf %lf %lf\n", &lat, &lng, &time) != EOF)
    {
        Point pt(lat,lng);
        //DisplayAPoint(pt);
        traj.push_back(pt);
        i++;
    }
    traj.resize(i);
    //DisplayAPoint(pt);
    //DisplayAPoint(traj[0]);
}

//map a trajectory
void MapTrajectory(std::vector <Point> traj/*, Grid grids[]*/)
{
    printf("map function\n");
    int size = traj.size();
    std::vector <Point> mapped_traj(size);
    
    std::vector <int> cadtGrid, cadtEdge;
    GetCandidateGrid(traj[0], cadtGrid);
    GetCandidateEdge(traj[0], cadtGrid, cadtEdge);
}


//get all the candidate grids
void GetCandidateGrid(Point pt, std::vector <int> &cadtGrid)
{
    Grid center = grids[pt.gid];
    printf("grid id: %d\n", pt.gid);
    bool flag[4];
    double dist[4]; //0:up, 1:right, 2:down, 3:left
    int tempindex[4] = {pt.gid+columns, pt.gid+1, pt.gid-columns, pt.gid-1};
    cadtGrid.push_back(pt.gid);
    
    //distance to the four lines of the grid
    dist[0] = dispToseg(pt, center.corner[0], center.corner[1]);
    dist[1] = dispToseg(pt, center.corner[1], center.corner[2]);
    dist[2] = dispToseg(pt, center.corner[2], center.corner[3]);
    dist[3] = dispToseg(pt, center.corner[3], center.corner[0]);
    
    DisplayAPoint(center.corner[0]);
    DisplayAPoint(center.corner[1]);
    DisplayAPoint(center.corner[2]);
    DisplayAPoint(center.corner[3]);
    
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
void GetCandidateEdge(Point pt, std::vector <int> &cadtGrid, std::vector <int> &cadtEdge)
{
    //use set in order to avoid some edges contained by more than one grid.
    std::set <int> AllCandidate;
    std::priority_queue < pair <double, int> > Q;
    int gridid， eid;
    double dist;
    int size;
    
    std::cout << "there are " << cadtGrid.size() << " candidate grids" << std::endl;
    for (int i = 0; i < cadtGrid.size(); i++)
    {
        gridid = cadtGrid[i];
        DisplayAGrid(grids[gridid]);
        AllCandidate.insert(grids[gridid].eids.begin(), grids[gridid].eids.end());
    }
    std::cout << "There are " << AllCandidate.size() << " candidate edges" << std::endl;
    
    if(AllCandidate.size() == 0)
        return;
    
    for (int i = 0; i < AllCandidate.size(); i++)
    {
        eid = AllCandidate[i];
        dist = distpToseg(pt, edges[eid].start, edges[eid].end);
        Q.push(std::make_pair(1/dist, eid));
        if (Q.size() > NumofCadt)
            Q.pop();
    }
    
    size = Q.size();
    for (int i = 0; i < size; i++)
    {
        cadtEdge.push_back(Q.top().second);
        Q.pop();
    }
}