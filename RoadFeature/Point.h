//
//  Points.hpp
//  
//
//  Created by XoX on 15/9/28.
//
//

#ifndef Points_hpp
#define Points_hpp

#include <stdio.h>
#include "stdafx.h"

const double eps = 1e-18;
//define the earth radius
#define EARTHRADIUS 6371000
const double PI = acos(-1.0);//get pi

//x<0 --- -1 ; x==0 --- 0 ; x>0 --- 1
inline int dcmp(double x){return (x > eps) - (x < -eps);}

//get the square of a data
template <class T>
T SQR(T x) {return x*x;}

/*
struct GeoPoint
{
	double latitude,longitude;
	Date date;
	GeoPoint(double lat,double lon,Date dat):latitude(lat),longitude(lon),date(dat){}
};
*/

// class Points
class Point
{
private:
    //get radian of a degree
    double getRad(double deg);
    
    //get degree of a radian
    double getDeg(double rad);
    
public:
    double x,y,z;//transfer a geometry point into one 3-d point
    int id;
    //default
    Point();
    
    Point(const Point& p):x(p.x),y(p.y),z(p.z),id(p.id){}
    
   // Point(const GeoPoint& p);
    
    Point( double _lon, double _lat);
    
    Point(double _x, double _y, int _id);
    
    Point(const double& _x,const double& _y,const double& _z);
    
    //return the euclude distance from point p(m);
    double EucDisTo(const Point& p);
    
    //retrun the geometry distance from point p(m);
    double GeoDisTo(Point& p);
    
    //return the degree of the two points
    double degBetween(Point& p);
    
    Point operator + (const Point& p);
    
    Point operator - (const Point& p);
    
    double operator * (const Point& p);
    
    Point operator * (const double& ratio);
    
    Point operator / (const double& ratio);
    
    bool operator == (const Point &p) const {return dcmp(x-p.x) == 0 && dcmp(y-p.y) == 0 && dcmp(z-p.z) == 0;}
    
    bool operator < (const Point &p) const
    {
        if (dcmp(y - p.y) == 0)
            return dcmp(x - p.x) <= 0;
        return dcmp(y - p.y) <= 0;
    }
    
    //return the norm of the vector;
    double length();
    
    //return the latitude of the point;
    double getLat();
    
    //return the longitude of the point;
    double getLon();
    
};

#endif /* Points_hpp */
