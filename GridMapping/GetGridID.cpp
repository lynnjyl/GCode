#include <iostream>
#include <fstream>
#include <set>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

double minlat = 39.41;
double minlng = 115.36;
double maxlat = 41.09;
double maxlng = 117.51;
double differ = 0.01;
int columns = (maxlng - minlng)/differ + 1;
int rows = (maxlat - minlat)/differ + 1;
int size = columns*rows;


int GetFirstGID(double lat, double lng)
{
    //printf("lat lng : %lf, %lf\n", lat, lng);
        //the map is divided into grids
    //int para = (maxlat - minlat)/differ + 1;    //printf("para: %i\n", para);
    int x, y;
    x = (lat - minlat)/differ;          //printf("x: %i\n", x);
    y = (lng - minlng)/differ+1;                          //printf("y: %i\n", y);
    return x*columns + y;
}


int GetLayer(int FirstID)
{
    int Layer;
    int x, y;
    x = FirstID/columns;
    y = FirstID%columns;

    if(x <= 65 && x > 45 && y <= 120 && y > 90)
        Layer = 1;
    else
    {
        if((x > 25||x <= 80)&&(y > 80||y <=130))
            Layer = 2;
        else
            Layer = 3;
    }
    return Layer;
}
int GetGridID(double lat, double lng, int FirstID)
{
    int GridID;
    int x, y;
    double dif1, dif2;
    int presum;
    double minlat_l1, minlng_l1, maxlng_l1;
    double minlat_l2, minlng_l2, maxlng_l2;
    int x_l1, x_l2, y_l1, y_l2;
    int columns_l1, columns_l2, gridid_l1, gridid_l2;

    dif1 = 0.0005;
    dif2 = 0.001;
    x = FirstID/columns;
    y = FirstID%columns;

    int layer = GetLayer(FirstID);
    switch(layer)
    {
        case 1:
            presum = 248538;
            minlat_l1 = minlat + differ*45;
            minlng_l1 = minlng + differ*90;
            maxlng_l1 = minlng + differ*120;
            x_l1 = (lat - minlat_l1)/dif1;
            y_l1 = (lng - minlng_l1)/dif1+1;
            columns_l1 = (maxlng_l1 - minlng_l1)/dif1+1;
            gridid_l1 = x_l1*columns_l1 + y_l1;
            GridID = presum + gridid_l1;
            break;
        case 2:
            presum = 33538;
            minlat_l2 = minlat + differ*25;
            minlng_l2 = minlng + differ*80;
            maxlng_l2 = minlng + differ*130;
            x_l2 = (lat - minlat_l2)/dif2;
            y_l2 = (lng - minlng_l2)/dif2+1;
            columns_l2 = (maxlng_l2 - minlng_l2)/dif2+1;
            gridid_l2 = x_l2*columns_l2 + y_l2;
            if(x <= 45)
                GridID = presum + gridid_l2;
            else
            {
                if(x > 65)
                    GridID = presum + 140000 + (x_l2 - 400) * 500 + y_l2;
                else
                {
                    if(y <= 90)
                        GridID = presum + 100000 + (x_l2 - 200) * 100 + y_l2;
                    else
                        GridID = presum + 100000 + 20000 + (x_l2 - 200) * 100 + y_l2;
                }
            }
            break;
        case 3:
            if(FirstID <= 5400)
                GridID = FirstID;
            else
            {
                if(FirstID > 17280)
                    GridID = 5400+4400+4730+(x-80)*216+y;
                else
                {
                    if(y <= 80)
                        GridID = 5400 + (x-25)*80+y;
                    else
                        GridID = 5400+4400+(x-25)*86+y;
                }
            }
            break;
    }
    return GridID;
}


int main(int argc, char *argv[])
{
    double lat, lng;
    char time[20];
    int FirstID, GridID;
    int num = atoi(argv[2]);
    FILE *fp;
    fp = fopen(argv[1], "r");

    set <int> grid_of_traj;
    set <int> ::iterator it;

    while(fscanf(fp, "%lf %lf %s\n", &lat, &lng, time) != EOF)
    {
        FirstID = GetFirstGID(lat, lng);
        GridID = GetGridID(lat, lng, FirstID);

//        cout << "(lat, lng) : " << lat << " " << lng << endl;
//        cout << "FirstID :" << FirstID << endl;
//        cout << "GridID : " << GridID << endl;
        grid_of_traj.insert(GridID);
    }
    fclose(fp);

    cout << "Begin to write." << endl;
    FILE *fp2 = fopen("matrix.txt", "a");

    for(it = grid_of_traj.begin(); it != grid_of_traj.end(); it++)
    {
        fprintf(fp2, "%d %d\n", num, *it);
    }

    fclose(fp2);
    cout << ">>>SUCCESS<<<" << endl;
    return 0;
}
