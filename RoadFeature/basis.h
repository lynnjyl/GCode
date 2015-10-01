//
//  basis.h
//  
//
//  Created by XoX on 15/9/17.
//
//

#ifndef _basis_h
#define _basis_h
#include "Point.h"
#include "stdafx.h"
/*
struct GPSPoint
{
    double lat;
    double lng;
    double time;
    int gid;
};
*/
struct Edge
{
    int eid;
    int start_vid, end_vid;
    Point start, end;
    //GPSPoint features[4];
   // int NumofFeature;
   // int gid[4];
};

struct Grid
{
	Point ld, ru;
	int gid;
	vector <int> eids;
};

double wallclock();

/*
void DisplayAnEdge(Edge edges)
{
	printf("============An Edge============\n");
	printf("  Edge ID		%i\n",edges.eid);
	printf("  Start_vid		%i\n", edges.start_vid);
	printf("  End_vid		%i\n", edges.end_vid);
	//printf("  Grid ID		%i", edge.gid[0]);
	//if(edge.gid.size() > 1)
	//	printf(" %i\n", edge.gid[1]);
	printf("==========End display==========\n");

}*/
void DisplayAnEdge(Edge edge);
void ReadVertices(Point vertices[], int NumofVer);
void ReadEdges(Edge edges[], Point vertices[], int NumofEdge);
void SetGrid(Grid grids[]);
/*
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
*/
#endif
