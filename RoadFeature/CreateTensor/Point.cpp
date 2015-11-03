//
//  Points.cpp
//  
//
//  Created by XoX on 15/9/28.
//
//

#include "Point.h"
#include "stdafx.h"
#include "basis.h"

///////////////////Point Class Begin//////////////////////

//get the radius of a degree
double Point::getRad(double deg)
{
    return PI/180.0*deg;
}

//get the degree of a point's radius
double Point::getDeg(double rad)
{
    double tmp = 180/PI*rad;
    if(tmp < 0)
        tmp = 180 + tmp;
    return tmp;
}

//construct
Point::Point():x(0),y(0),z(0){}

/*
Point::Point(const GeoPoint& p)
{
    double lon = getRad(p.longitude);
    double lat = getRad(p.latitude);
    x = cos(lat)*cos(lon);
    y = cos(lat)*sin(lon);
    z = sin(lat);
}

*/
/*
Point::Point(double _x, double _y, int _id):id(_id)
{
    double lon = getRad(_x);
    double lat = getRad(_y);
    x = cos(lat)*cos(lon);
    y = cos(lat)*sin(lon);
    z = sin(lat);
}
*/
Point::Point(double _lat,double _lon)
{
    if(_lat == 0 && _lon == 0)
    {
        gid = 0;
        _lon = 0;
        _lat = 0;
        x = y = z =0;
    }
    else
    {
        gid = GetGID(_lat,_lon);
        _lon = getRad(_lon);
        _lat = getRad(_lat);
        //printf("gid : %i\n", gid);
        x = cos(_lat)*cos(_lon);
        y = cos(_lat)*sin(_lon);
        z = sin(_lat);
    }
}


Point::Point(const double& _x,const double& _y,const double& _z):x(_x),y(_y),z(_z)
{
    
}

//return the eulude distance between two points
double Point::EucDisTo(const Point& p)
{
    return EARTHRADIUS*sqrt(SQR(x-p.x)+SQR(y-p.y)+SQR(z-p.z));
}

//return the geometry distance between two points
double Point::GeoDisTo(Point& p)
{
    //return EARTHRADIUS*sqrt(SQR(x-p.x)+SQR(y-p.y)+SQR(z-p.z));
    double cosTheta = degBetween(p);
    return EARTHRADIUS*sqrt(fabs(1.0-SQR(cosTheta)));
}

//return the degree between two points
double Point::degBetween(Point& p)
{
    return (*this * p) / (length()*p.length());
}

Point Point::operator + (const Point& p)
{
    return Point(x+p.x,y+p.y,z+p.z);
}

Point Point::operator - (const Point& p)
{
    return Point(x-p.x,y-p.y,z-p.z);
}

double Point::operator * (const Point& p)
{
    return x*p.x + y*p.y + z*p.z;
}

Point Point::operator * (const double& ratio)
{
    return Point(x*ratio,y*ratio,z*ratio);
}

Point Point::operator / (const double& ratio)
{
    if(ratio == 0)
    {
        fprintf(stderr,"vector devided by zero!\n");
//        system("pause");
//        exit(-1);
    }
    return Point(this->x/ratio,this->y/ratio,this->z/ratio);
}
double Point::length()
{
    return sqrt(SQR(x)+SQR(y)+SQR(z));
}

double Point::getLat()
{
    //assert(z >=-1 && z <= 1);
    return getDeg(asin(z));
}

double Point::getLon()
{
    //assert(fabs(x) > eps);
    return getDeg(atan(y/x));
}
///////////////////Point Class End//////////////////////


Point pToseg(Point p,Point begin,Point end){
    Point retVal;
    
    double dx = begin.x - end.x;
    double dy = begin.y - end.y;
    double dz = begin.z - end.z;
    if(fabs(dx) < eps && fabs(dy) < eps && fabs(dz) < eps )
    {
        //printf("one\n");
        retVal = begin;
        return retVal;
    }
    
    double v1 = ((p-begin)*(end-begin));
    double v2 = ((p-end)*(begin-end));
    if(  v1*v2  < 0)
    {
        //printf("two\n");
        return p.EucDisTo(begin) < p.EucDisTo(end)?begin:end;
    }
    
    double u = (p.x - begin.x)*(begin.x - end.x)
    + (p.y - begin.y)*(begin.y - end.y)
    + (p.z - begin.z)*(begin.z - end.z);
    u = u/((dx*dx)+(dy*dy)+(dz*dz));
    
    retVal.x = begin.x + u*dx;
    retVal.y = begin.y + u*dy;  
    retVal.z = begin.z + u*dz;
    //printf("three\n");
    return retVal;  
}

double dispToseg(Point p,Point a,Point b)
{
    //printf("disptoseg\n");
    Point tmp = pToseg(p,a,b);
    //DisplayAPoint(tmp);
    return p.EucDisTo(tmp);
}
