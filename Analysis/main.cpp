#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;

double minlat = 39.41;
double minlng = 115.36;
double maxlat = 41.09;
double maxlng = 117.51;
double differ = 0.01;
int columns = (maxlng - minlng)/differ + 1;
int rows = (maxlat - minlat)/differ + 1;
int size = columns*rows;

int GetGID(double lat, double lng)
{
    //printf("lat lng : %lf, %lf\n", lat, lng);
        //the map is divided into grids
    //int para = (maxlat - minlat)/differ + 1;    //printf("para: %i\n", para);
    int x, y;
    x = (lat - minlat)/differ;          //printf("x: %i\n", x);
    y = (lng - minlng)/differ + 1;              //printf("y: %i\n", y);
        return x*columns + y;
}


int main(int argc, char * argv[])
{
    cout << "Hello world!" << endl;

//    string filename=argv[1];
    double lat, lng;
    char time[20];
    vector <int> grid, num_of_grids;
    int gid;
    unsigned int i;
    bool flag = false;
    FILE *fp = fopen(argv[1], "r");

    while(fscanf(fp, "%lf %lf %s\n", &lat, &lng, time) != EOF)
    {
        gid = GetGID(lat, lng);
        //cout << i << " " << gid << endl;
        for(i = 0; i < grid.size(); i++)
        {
            if(gid == grid[i])
            {
                flag = true;
                num_of_grids[i]++;
                break;
            }
        }
        if(!flag)
        {
            grid.push_back(gid);
            num_of_grids.push_back(1);
        }
        flag = false;
        //i++;
    }

    fclose(fp);

    cout << "finish reading!" << endl;
    FILE *fp2 = fopen("analysis.txt", "a");
    for(i =0; i < grid.size(); i++)
    {
        //cout << grid[i] << " " << num_of_grids[i] << endl;
        fprintf(fp2, "%d %d\n", grid[i], num_of_grids[i]);
    }
    fclose(fp2);
    cout << ">>>>SUCCESS<<<<" << endl;


    return 0;
}
