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

double wallclock();


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

}
#endif
