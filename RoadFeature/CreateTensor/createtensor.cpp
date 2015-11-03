#include "stdafx.h"
#include "Point.h"
#include "basis.h"
using namespace std;

extern double * EdgeLength;
extern vector <Point>  TrajPoint;
extern vector <int> TrajEdge;
extern vector <string> TrajTime;
extern vector <int> EdgeID;
extern vector <int> TimeSector;
extern vector <double> Ratio;

void ReadTrajEdges(string filename)
{
    FILE *fp;
    fp = fopen(filename.c_str(), "r");
    int Edgeid;
    char time[20];
    while(fscanf(fp, "%d %s\n", &Edgeid, time)  != EOF)
    {
        TrajEdge.push_back(Edgeid);
        string strtime(time);
        TrajTime.push_back(strtime);
    }
    cout << "Read Trajectory Edges finished!" << endl;
}
void ReadTrajPoints(string filename)
{
    FILE *fp;
    fp = fopen(filename.c_str(), "r");
    double lat, lng;
    while(fscanf(fp, "%lf %lf\n", &lat, &lng) != EOF)
    {
        Point pt(lat, lng);
        TrajPoint.push_back(pt);
    }
    cout <<"Read Trajectory Matched Points finished!" << endl;
}

int GetTimeSector(string TrajTime, int TimeInterval)
{
    int TimeSetr;
    int hour, minute;
    int p1, p2;

    p1 = TrajTime.find_first_of(':', 0);
    hour = atoi(TrajTime.substr(0, p1++).c_str());
    p2 = TrajTime.find_first_of(':', p1);
    minute = atoi(TrajTime.substr(p1, p2-p1).c_str());

    if(TimeInterval == 60)
    {
        TimeSetr = hour + 1;
    }
    if(TimeInterval == 30)
    {
        TimeSetr = 2*hour + 1;
        if(minute >= 30)
            TimeSetr++;
    }
    return TimeSetr;
}
void CreateTensor(int TrajId, int TimeInterval)
{
    int size = TrajEdge.size();
    int i = 0, start, end;
    unsigned int j;
    int currenteid;
    int TimeSetr;
    bool flag;
    double dist, ratio;
    while(i < size)
    {
        //cout << i << endl;
        flag = false;
        TimeSetr = GetTimeSector(TrajTime[i], TimeInterval);
        currenteid = TrajEdge[i];
        start = i;

        while((i+1 < size) && (TrajEdge[i+1] == currenteid) && (GetTimeSector(TrajTime[i+1], TimeInterval) == TimeSetr) )
            i++;

        //cout << endl;
        end = i++;

        //cout << "ok here" << endl;

        dist = TrajPoint[start].EucDisTo(TrajPoint[end]);
        ratio = dist/EdgeLength[currenteid];

        //cout << currenteid << " " << TimeSetr << " " << ratio << endl;

        for(j = 0; j < EdgeID.size(); j++)
        {
            if(EdgeID[j] == currenteid && TimeSector[j] == TimeSetr)
            {
                flag = true;
                if(Ratio[j] < ratio)
                    Ratio[j] = ratio;
            }
        }
        //cout << "here" << endl;
        if(!flag && (currenteid != 0) && (ratio !=0 ))
        {
            //cout << "here" << endl;
            EdgeID.push_back(currenteid);
            TimeSector.push_back(TimeSetr);
            Ratio.push_back(ratio);
        }
    }

    //cout << "ok here" << endl;
    FILE *fp;
    fp = fopen("tensor.txt", "a+");
    for(j = 0; j < EdgeID.size(); j++)
        fprintf(fp, "%d %d %d %lf\n", TrajId, EdgeID[j], TimeSector[j], Ratio[j]);

    cout << "Write to tensor.txt finished" << endl;
}

