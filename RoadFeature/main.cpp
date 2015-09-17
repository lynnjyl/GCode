//
//  main.cpp
//  
//
//  Created by XoX on 15/9/17.
//
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "include/basis.h"
using namespace std;
int NumofVer = 171504;


void ReadVertices(GPSPoint vertices[])
{
    //printf("hell function\n");
    FILE * fp;
    fp = fopen("./roadnetwork/vertices.txt", "r+");
    char str[200];
    int eid;
    double lat, lng;
    for(int i = 0; i < NumofVer; i++)
    {
        fscanf(fp,"%i %lf %lf", &eid, &lat, &lng);
        vertices[eid].lat = lat;
        vertices[eid].lng = lng;
    }
}


int main(int argc, char * argv[])
{
    //Read vertices file;
    double t1 = wallclock();
    GPSPoint vertices[NumofVer];
    ReadVertices(vertices);
    double t2 = wallclock();
    printf("Reading time is: %lf\n", t2-t1);
}
