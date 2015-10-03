#include "stdafx.h"
#include "Point.h"
#include "basis.h"
const double minlat = 39.4;
const double minlng = 115.3;
const double maxlat = 41.1;
const double maxlng = 117.6;
const double differ = 0.05;


void DisplayAPoint(Point pt)
{
    printf("============A Point============\n");
    printf("  Point x y z :               %lf, %lf, %lf\n", pt.x, pt.y, pt.z);
    printf("==========End display==========\n");
}

void DisplayAnEdge(Edge edge)
{
        printf("============An Edge============\n");
        printf("  Edge ID               %i\n",edge.eid);
        printf("  Start_vid             %i\n", edge.start_vid);
        printf("  End_vid               %i\n", edge.end_vid);
        printf("==========End display==========\n");

}

void DisplayAGrid(Grid grid)
{
    int size = grid.eids.size();
    int i;
    printf("============A  Grid============\n");
    printf("  Grid ID               %i\n", grid.gid);
    printf("  Edges in the Grid:\n");
    for(i = 0; i < size; i++)
    {
        if(i%5 == 0 && i != 0)
            printf("\n");
        printf(" %i", grid.eids[i]);
    }
    printf("\n");
    printf("==========End display==========\n");
}

int GetGID(double lat, double lng)
{
        //the map is divided into grids
    int para = (maxlat - minlat)/differ + 1;
    int x, y;
        x = (lat - minlat)/differ + 1;
        y = (lng - minlng)/differ;
        return para*y+x;
}


void ReadVertices(Point vertices[], int NumofVer)
{
    printf("hello function\n");
    FILE * fp;
    fp = fopen("./roadnetwork/vertices.txt", "r+");
    //char str[200];
    int vid;
    double lat, lng;
    for(int i = 0; i < NumofVer; i++)
    {
        fscanf(fp,"%i %lf %lf", &vid, &lat, &lng);
        Point pt(lng,lat);
        vertices[vid] = pt;
        //vertices[vid].lat = lat;
        //vertices[vid].lng = lng;
        //vertices[vid].gid = GetGID(lat, lng);
        //cout << lat << " " << lng << " " << vertices[eid].gid << endl;
    }
}

void ReadEdges(Edge edges[], Point vertices[], int NumofEdge)
{
        printf("Hello Reading Edges!!\n");
        FILE * fp;
        fp = fopen("./roadnetwork/edges.txt", "r+");
        int eid, start_vid, end_vid;
        printf("file open\n");
        for(int i = 0; i < NumofEdge; i++)
        {
                fscanf(fp, "%i %i %i", &eid, &start_vid, &end_vid);
                edges[eid].eid = eid;
                edges[eid].start_vid = start_vid;
                edges[eid].end_vid = end_vid;
                edges[eid].start = vertices[start_vid];
                edges[eid].end = vertices[end_vid];
        }
}

void SetGrid(Grid grids[], std::string grid_edge)
{

	int lngbound = (maxlng - minlng)/differ + 1;
	int latbound = (maxlat - minlat)/differ + 1;
	int x, y;
	x = y = 0;
	int index;
	
	while(y < lngbound)
	{
		while(x < latbound)
		{	
			index = x + y*latbound;
			Point ld(minlat + x*differ, minlng + y*differ);
        		Point ru(minlat + (x+1)*differ, minlng + (y+1)*differ);

			grids[index].ld = ld;
			grids[index].ru = ru;
			grids[index].gid = index;
			x++;
		}
		y++;	
	}
	
	//set the vector eids
	//read grid_edge file
    std::ifstream ifs(grid_edge.c_str());
    std::string str;
    while (!ifs.eof())
    {
        getline(ifs, str);
        SetGridofEid(str, grids);
    }
}

void SetGridofEid(std::string str, Grid grids[])
{
    int p1, p2, p3;
    int gid, eid;
    
    p1 = str.find(' ', 0);
    if(p1 < 0)
        return;
    gid = atoi(str.substr(0, p1++).c_str());
    grids[gid].gid = gid;
    
    while(p2 >= 0)
    {
        p2 = str.find(' ', p1);
        eid = atoi(str.substr(p1, p2-p1).c_str());
        grids[gid].eids.push_back(eid);
        p1 = p2 + 1;
    }
}
