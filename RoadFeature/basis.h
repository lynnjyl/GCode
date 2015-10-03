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

struct Edge
{
    int eid;
    int start_vid, end_vid;
    Point start, end;
};

struct Grid
{
	Point ld, ru;
	int gid;
    std::vector <int> eids;
};

//time.cpp
double wallclock();

//datapreprocess.cpp
void DisplayAPoint(Point pt);
void DisplayAnEdge(Edge edge);
void DisplayAGrid(Grid grid);
void ReadVertices(Point vertices[], int NumofVer);
void ReadEdges(Edge edges[], Point vertices[], int NumofEdge);
void SetGridofEid(std::string str, Grid grids[]);
void SetGrid(Grid grids[], std::string grid_edge);

#endif
