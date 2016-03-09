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

const int NumofVer = 171504;
const int NumofEdge = 433391;
int Max = 92645;
double minlat = 39.4;
double minlng = 115.3;
double maxlat = 41.1;
double maxlng = 117.6;
double differ = 0.05;
int columns = (maxlng - minlng)/differ + 1;
int rows = (maxlat - minlat)/differ + 1;
int size = columns*rows;
//GPSPoint vertices[NumofVer];
Edge *edges = new Edge[NumofEdge+1];
Point *vertices = new Point[NumofVer+1];
Grid *grids = new Grid[size];
std::vector <Point> traj;
//Trajectory mapped_traj;

int main(int argc, char * argv[])
{
    std::string grid_edge_file = argv[1];
    std::string trajectoryfile = argv[2];
    //std::string directory = argv[2];

    /*data pre-process.*/
    // step 1: set grid information.
    SetGrid(grids, grid_edge_file);
    //printf("there are %d grids\n", size);
	// step 2: read vertices file & set them.
    //printf("begin to read\n");
	ReadVertices(vertices, NumofVer);
	//printf("end reading vertices\n");
    // step 3: read edge file & set them
	ReadEdges(edges, vertices, NumofEdge);
	//printf("Finish Reading edges\n");
    //DisplayAnEdge(edges[1]);
    //map-matching part
    // step 1: read one trajectory;
    ReadTrajectory(trajectoryfile, traj);
    //printf("end reading trajectory \n");
    //step 2: map it top the map
    MapTrajectory(traj, trajectoryfile);




}
