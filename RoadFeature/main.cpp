//
//  main.cpp
//  
//
//  Created by XoX on 15/9/17.
//
//maxlat = 41.083333 minlat = 39.416667
//maxlng = 115.37500 minlng = 117.50000
/*
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>*/
#include "stdafx.h"
#include "basis.h"
#include "Point.h"
using namespace std;
const int NumofVer = 171504;
const int NumofEdge = 433391;
const double minlat = 39.4;
const double minlng = 115.3;
const double maxlat = 41.1;
const double maxlng = 117.6;
const double differ = 0.05;
const int size = ((maxlng - minlng)/differ + 1)*((maxlat - minlat)/differ + 1);
//GPSPoint vertices[NumofVer];
Edge edges[NumofEdge+1];
Point vertices[NumofVer+1];
Grid *grids;
/*
int GetGID(double lat, double lng)
{
	//the map is divided into 10x10 grids
	int x, y;
	x = (lat - minlat)/0.17 + 1;
	y = (lng - minlng)/0.23;
	return 10*y+x;
}

void ReadVertices(Point vertices[])
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

void ReadEdges(Edge edges[], Point vertices[])
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
int main(int argc, char * argv[])
{
//	Edge edges[NumofEdge+1];
//	Edge edges[NumofEdge+1];
//	Point vertices[NumofVer+1];
    std::string grid_edge = argv[1];
    grids = new Grid[size];
    SetGrid(grids, grid_edge);
    DisplayAGrid(grids[5]);
    DisplayAGrid(grids[41]);
	printf("there are %d grids\n", size);
	/*
    printf("begin to read\n");
	ReadVertices(vertices, NumofVer);
	ReadEdges(edges, vertices, NumofEdge);
	printf("Finish Reading\n");
	DisplayAnEdge(edges[1]);*/
}
