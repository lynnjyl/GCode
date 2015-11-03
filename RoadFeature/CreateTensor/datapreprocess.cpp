#include "stdafx.h"
#include "Point.h"
#include "basis.h"
extern double minlat;
extern double minlng;
extern double maxlat;
extern double maxlng;
extern double differ;
extern int rows;
extern int columns;


void DisplayAPoint(Point pt)
{
    printf("============A Point============\n");
    printf("  Point x y z : %lf, %lf, %lf\n", pt.x, pt.y, pt.z);
    printf("     Grid ID  : %i\n", pt.gid);
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
    //printf("lat lng : %lf, %lf\n", lat, lng);
        //the map is divided into grids
    //int para = (maxlat - minlat)/differ + 1;    //printf("para: %i\n", para);
    int x, y;
    x = (lat - minlat)/differ;          //printf("x: %i\n", x);
    y = (lng - minlng)/differ + 1;              //printf("y: %i\n", y);
        return x*columns + y;
}


void ReadVertices(Point vertices[], int NumofVer)
{
    //printf("hello function\n");
    FILE * fp;
    fp = fopen("../roadnetwork/vertices.txt", "r+");
    //char str[200];
    int vid;
    double lat, lng;
    for(int i = 0; i < NumofVer; i++)
    {
        fscanf(fp,"%i %lf %lf", &vid, &lat, &lng);
        Point pt(lat,lng);
        vertices[vid] = pt;
    }
}

void ReadEdges(Edge edges[], Point vertices[], int NumofEdge)
{
        //printf("Hello Reading Edges!!\n");
        FILE * fp;
        fp = fopen("../roadnetwork/edges.txt", "r+");
        int eid, start_vid, end_vid;
        //printf("file open\n");
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
	//int lngbound = (maxlng - minlng)/differ + 1;
	//int latbound = (maxlat - minlat)/differ + 1;
    //printf("rows : %i\n", rows);
    //printf("columns : %i\n", columns);
	int x, y;
	x = y = 0;
	int index;

	while(y < rows)
	{
        x = 0;
		while(x < columns)
		{
			index = x + y*columns;
			Point ld(minlat + x*differ, minlng + y*differ);
            Point ru(minlat + (x+1)*differ, minlng + (y+1)*differ);
            Point lu(minlat + (x+1)*differ, minlng + y*differ);
            Point rd(minlat + x*differ, minlng + (y+1)*differ);

			grids[index].corner[0] = lu;
			grids[index].corner[1] = ru;
            grids[index].corner[2] = rd;
            grids[index].corner[3] = ld;
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
    int p1, p2;
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
