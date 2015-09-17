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

#endif
