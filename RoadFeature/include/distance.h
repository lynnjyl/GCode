// 
//	distance.h
//
//measure distance between two gps points
//
//	Created by Yiling on 15/9/24

#ifndef _distance_h
#define _distance_h

#define pi 3.141592653.14159265358979323846
#include <math.h>

double deg2rad(double deg)
{
        return (deg * pi / 180);
}

double rad2deg(double rad)
{
        return (rad * 180 / pi);
}

double distance(double &lat1, double &lon1, double &lat2, double &lon2)
{
        double theta, dist;

        theta = lon1 - lon2;
        dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));

        dist = acos(dist);
        dist = rad2deg(dist);
        dist = dist * 60 * 1.1515;
        dist = dist * 1609.344;
        return (dist);
}

#endif
