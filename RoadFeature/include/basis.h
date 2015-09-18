//
//  basis.h
//  
//
//  Created by XoX on 15/9/17.
//
//

#ifndef _basis_h
#define _basis_h


#include <vector>

struct GPSPoint
{
    double lat;
    double lng;
    double time;
    int gid;
};

struct Edges
{
    int eid;
    int start_vid, end_vid;
    GPSPoint start, end;
    std::vector <GPSPoint> features;
    std::vector <int> gid;
};

double wallclock();


void DisplayAnEdge(Edges edge)
{
	printf("============An Edge============\n");
	printf("  Edge ID		%i\n",edge.eid);
	printf("  Start_vid		%i\n", edge.start_vid);
	printf("  End_vid		%i\n", edge.end_vid);
	printf("  Grid ID		%i", edge.gid[0]);
	if(edge.gid.size() > 1)
		printf(" %i\n", edge.gid[1]);	
	printf("==========End display==========\n");

}
#endif
