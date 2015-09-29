//
//  main.cpp
//  
//
//  Created by XoX on 15/9/17.
//
//maxlat = 41.083333 minlat = 39.416667
//maxlng = 115.37500 minlng = 117.50000

#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "include/basis.h"
using namespace std;
const int NumofVer = 171504;
const int NumofEdge = 433391;
double minlat = 39.4;
double minlng = 115.3;
double maxlat = 41.1;
double maxlng = 117.6;
//GPSPoint vertices[NumofVer];
int GetGID(double lat, double lng)
{
	//the map is divided into 10x10 grids
	int x, y;
	x = (lat - minlat)/0.17 + 1;
	y = (lng - minlng)/0.23;
	return 10*y+x;
}

void ReadVertices(GPSPoint vertices[])
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
        vertices[vid].lat = lat;
        vertices[vid].lng = lng;
        vertices[vid].gid = GetGID(lat, lng);
	//cout << lat << " " << lng << " " << vertices[eid].gid << endl;
    }
}

void ReadEdges(Edges edge[], GPSPoint vertices[])
{
	printf("Hello Reading Edges!!\n");
	FILE * fp;
	fp = fopen("./roadnetwork/edges.txt", "r+");
	int eid, start_vid, end_vid;
	printf("file open\n");
	for(int i = 0; i < NumofEdge; i++)
	{
		fscanf(fp, "%i %i %i", &eid, &start_vid, &end_vid);
		edge[eid].eid = eid;
		edge[eid].start_vid = start_vid;	
		edge[eid].end_vid = end_vid;
	}
}
int main(int argc, char * argv[])
{
	Edges edge[NumofEdge+1];
	ReadVertices(vertices);
	//ReadEdges(edge, vertices);
	printf("Finish Reading\n");
	//DisplayAnEdge(edge[1]);
}
