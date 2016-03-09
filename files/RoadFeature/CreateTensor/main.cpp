#include <iostream>
#include "stdafx.h"
#include "basis.h"
#include "Point.h"

using namespace std;
const int NumofVer = 171504;
const int NumofEdge = 433391;
int Max = 92645;
double minlat = 39.4;
double minlng = 115.3;
double maxlat = 41.1;
double maxlng = 117.6;
double differ = 0.05;
int columns = (maxlng - minlng)/differ + 1;
int rows = (maxlat - minlat)/differ + 1;
int size = columns*rows;
//GPSPoint vertices[NumofVer];
Edge *edges = new Edge[NumofEdge+1];
Point *vertices = new Point[NumofVer+1];
Grid *grids = new Grid[size];

double *EdgeLength = new double[NumofEdge+1];
vector <Point>  TrajPoint;
vector <int> TrajEdge;
vector <string> TrajTime;
vector <int> EdgeID;
vector <int> TimeSector;
vector <int> Ratio;

//Get edges length
void GetEdgeLength()
{
    int i;
    double dist;
    for(i = 1; i < NumofEdge + 1; i++)
    {
        dist = edges[i].start.EucDisTo(edges[i].end);
        EdgeLength[i] = dist;
    }
}



int main(int argc, char * argv[])
{
    int TrajId = atoi(argv[1]);
    string TrajEdgeFile = argv[2];
    string TrajPointFile = argv[3];
    int TimeInterval = atoi(argv[4]);

    //step one: read two files: edges & vertices
    ReadVertices(vertices, NumofVer);
	ReadEdges(edges, vertices, NumofEdge);
	//step two: get edges length.
	GetEdgeLength();
	//step three: read trajectory files;
	ReadTrajEdges(TrajEdgeFile);
	ReadTrajPoints(TrajPointFile);
	cout << ">>>>>>>SUCCEED<<<<<<<" << endl;

	//step four: create tensor;
	CreateTensor(TrajId, TimeInterval);




    return 0;
}
