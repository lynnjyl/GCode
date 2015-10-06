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

extern int Max;

struct Edge
{
    int eid;
    int start_vid, end_vid;
    Point start, end;
};

struct Grid
{
	Point corner[4]; // 0:left up, 1: right up, 2: right down, 3: left down
	int gid;
    std::vector <int> eids;
};
/*
struct Trajectory
{
    vector <Point>;
    int length
};
*/
struct Candidate
{
    bool cant[4]; //left 0, up 1, right 2, down 3
    int gid;
};

//time.cpp
double wallclock();

//datapreprocess.cpp
void DisplayAPoint(Point pt);
void DisplayAnEdge(Edge edge);
void DisplayAGrid(Grid grid);
int GetGID(double lat, double lng);
void ReadVertices(Point vertices[], int NumofVer);
void ReadEdges(Edge edges[], Point vertices[], int NumofEdge);
void SetGridofEid(std::string str, Grid grids[]);
void SetGrid(Grid grids[], std::string grid_edge);

//mapmatching.cpp
double partscore(Point pi, Point pj, Edge edge, bool flag);
void ReadTrajectory(std::string filename, std::vector <Point> &traj);
void GetCandidateGrid(Point pt, std::vector <int> &cadtGrid);
void GetCandidateEdge(Point pt, std::vector <int> &cadtGrid, std::vector <int> &cadtEdge);
void MapTrajectory(std::vector <Point> traj, std::string filename);

#endif
