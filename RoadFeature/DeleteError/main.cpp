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
std::vector <Point> traj;
std::vector <string> ptime;
std::vector <int> timeindex;
//Trajectory mapped_traj;


void GetMatchedFileName(string str1, string &str2, string &str3)
{
    int pos1 = str1.find_first_of('/', 0);
    pos1++;
    int pos2 = str1.find_first_of('/', pos1);
    pos2++;
    string temp = str1.substr(pos2, str1.length() - pos2);
    cout << temp << endl;
    str2 = "../matched/" +temp +"_traj.txt";
    str3 = "../matched/" +temp +"_edge.txt";
}
void ReadMatchedEdge(string MatchedEdgeFile, vector <int> &MatchedEID)
{
    cout << "Hello From ReadMatchedEdge!" << endl;
    cout << MatchedEdgeFile << endl;
    FILE *fp = fopen(MatchedEdgeFile.c_str(), "r");
    int eid, index = 0;
    vector <int> DetectEID;
    vector <int> DetectIdx;
    int CurrID = -1;
    unsigned int i = 0;
    unsigned int size;
    int front, middle, back;
    while (fscanf(fp, "%d\n", &eid) != EOF)
    {
        //cout << eid << endl;
        MatchedEID.push_back(eid);
        if(CurrID != eid)
        {
            DetectEID.push_back(eid);
            DetectIdx.push_back(index);
            CurrID = eid;
        }
        index++;
    }
    fclose(fp);

    size = DetectEID.size();
//    for(i = 0; i <size; i++)
//    {
//        cout << DetectIdx[i] << " " << DetectEID[i] << endl;
//    }

    cout << "size is " << size << endl;
    for(i = 0;  i < size-2; i++)
    {
        front = DetectIdx[i+1] - DetectIdx[i];
        middle = DetectIdx[i+2] - DetectIdx[i+1];
        if(i+3 == size)
            back = index - DetectIdx[i+2];
        else
            back = DetectIdx[i+3] - DetectIdx[i+2];

        //cout << i << " " <<  front << " " << middle << " " << back << endl;

        if(DetectEID[i] == DetectEID[i+2] && front > middle && back > middle && DetectEID[i] != 0)
        {
            cout << "At Line " << DetectIdx[i+1] << " change " << middle << " numbers of " << DetectEID[i+1] << " ---------> " << DetectEID[i] <<endl;
            for(int k =0; k < middle; k++)
            {
                MatchedEID[DetectIdx[i+1] + k] = DetectEID[i];
            }
        }
    }

    cout << "ok here" << endl;
//    for(i = 0; i < index; i++)
//        cout << MatchedEID[i] << endl;


}

void GetTime(vector <string> time)
{
    unsigned int i = 0;
    int p;
    int index;
    string temp;
    for (i = 0; i < time.size(); i++)
    {
        p = time[i].find_first_of(':');
        temp = time[i].substr(0, p);
        index = atoi(temp.c_str());
        timeindex.push_back(index);
        cout <<index << endl;
    }

}
void DetectError(string MatchedTrajFile, string MatchedEdgeFile)
{
    cout << "Hello From DetectError!" << endl;
    vector <int> MatchedEID;
    vector <Point> MatchedTraj;
    Point nomatched(0,0);
    Point MatchedPoint;
    double lat, lng;

    ReadMatchedEdge(MatchedEdgeFile, MatchedEID);


    MatchedEdgeFile.replace(3, 7, "modified");
    MatchedTrajFile.replace(3, 7, "modified");
    cout << MatchedEdgeFile << endl;
    FILE *fpedge, *fptraj;
    fpedge =fopen(MatchedEdgeFile.c_str(), "w");
    fptraj = fopen(MatchedTrajFile.c_str(), "w");
    unsigned int i, size = MatchedEID.size();
    //cout << traj[374].getLat() << " " << traj[374].getLon() << endl;
	//cout << traj[374].getLat() << " " << traj[374].getLon() << endl;
    GetTime(ptime);
    for(i = 0; i < size; i++)
    {
        if(MatchedEID[i] == 0)
        {
         //   MatchedPoint = nomatched;
            lat = lng = 0;
        }
        else
        {
            MatchedPoint = pToseg(traj[i], edges[MatchedEID[i]].start, edges[MatchedEID[i]].end);
            //cout <<i  << " " << traj[i].getLat() << " " << traj[i]. getLon() << endl;
            lat = MatchedPoint.getLat();
            lng = MatchedPoint.getLon();
            //cout << lat << " " << lng << endl;
        }

        fprintf(fpedge, "%d %d\n", MatchedEID[i], timeindex[i]);
        fprintf(fptraj, "%lf %lf\n", lat, lng);
    }
    fclose(fpedge);
    fclose(fptraj);


}
int main(int argc, char * argv[])
{
    //std::string grid_edge_file = argv[1];
    string trajectoryfile = argv[1];
    string MatchedTrajFile, MatchedEdgeFile;
    cout << trajectoryfile << endl;

    GetMatchedFileName(trajectoryfile.c_str(), MatchedTrajFile, MatchedEdgeFile);
    cout << MatchedEdgeFile << endl;
    cout << MatchedTrajFile << endl;

    //step one : read vertices file
	ReadVertices(vertices, NumofVer);
    // step two: read edge file & set them
	ReadEdges(edges, vertices, NumofEdge);
	std::cout << "read two file finished!" << std::endl;
    // step three： read raw gps file
	ReadTrajectory(trajectoryfile.c_str(), traj, ptime);
	//DisplayAPoint(traj[0]);
	//cout << traj[0].getLat() << " " << traj[0].getLon() << endl;
	//cout << traj[1].getLat() << " " << traj[1].getLon() << endl;
	std::cout << "read trajectory succeed!" << std::endl;
	// step 4: read matched edges
	DetectError(MatchedTrajFile, MatchedEdgeFile);



    return 0;

}
