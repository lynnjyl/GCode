#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;

double minlat = 39.41;
double minlng = 115.36;
double maxlat = 41.09;
double maxlng = 117.51;
//double differ1, differ2;
int columns, rows;


int GetGID(double lat, double lng, double differ1, double differ2, int columns)
{
    //printf("lat lng : %lf, %lf\n", lat, lng);
        //the map is divided into grids
    //int para = (maxlat - minlat)/differ + 1;    //printf("para: %i\n", para);
    //cout << lat << " " << lng << endl;
    //cout << differ1 << " " << differ2 << " " << columns << endl;
    int x, y;
    x = (lat - minlat)/differ1;          //printf("x: %i\n", x);
    y = (lng - minlng)/differ2 + 1;              //printf("y: %i\n", y);
        return x*columns + y;
}


int main(int argc, char * argv[])
{
    cout << "Hello world!" << endl;
    //cout << columns << " " << rows << " " << size << endl;
//    string filename=argv[1];
    
    double lat, lng;
    char time[20];
    vector <int> grid, num_of_grids;
    int gid;
    unsigned int i;
    bool flag = false;
    FILE *fp = fopen(argv[1], "r");
    double differ1 = atof(argv[2]);        //difference of latitude
    double differ2 = atof(argv[3]);        //difference of longitude
    
    int columns = (maxlng - minlng)/differ2 + 1;
    int rows = (maxlat - minlat)/differ1 + 1;
    int size = columns*rows;

    while(fscanf(fp, "%lf %lf %s\n", &lat, &lng, time) != EOF)
    {
        //cout << lat << " " << lng << endl;
        gid = GetGID(lat, lng, differ1, differ2, columns);
        //cout << i << " " << gid << endl;
        
        if (gid <= size)
        {
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
