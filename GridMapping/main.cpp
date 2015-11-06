/*
        Get all stay points in the dataset
	input parameter:
		[1] Number	: file name in ../Geolife Trajectories 1.3/Data/
		[2]	D		: distance threshold
		[3] T		: time threshold
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <sstream>

using namespace std;

#define pi 3.14159265358979323846

struct GPSlog
{
	double Latitude;
	double Longitude;
	string Time;
};

struct StayPoints
{
	double Lat;
	double Lngt;
	double arvT;
	double levT;
};

double deg2rad(double deg)
{
	return (deg * pi / 180);
}

double rad2deg(double rad)
{
	return (rad * 180 / pi);
}

double GetTime(string str)
{
    double time;
    int p1, p2;
    int hour, minute, second;
    p1 = str.find_first_of(':', 0);
    p2 = str.find_last_of(':');
   // cout << "p1 = " << p1 << " p2 = " << p2 << endl;
    hour = atoi(str.substr(0, p1).c_str());
    p1++;
    minute = atoi(str.substr(p1, p2-p1).c_str());
    p2++;
    second = atoi(str.substr(p2, str.length()-p2).c_str());
    //cout << hour << ":" << minute << ":" << second << endl;
    //cout << str << endl;
    time = hour*60*60+minute*60+second;
    return time;
}

double timebetween(GPSlog &l1, GPSlog &l2)
{
    //cout << "in time between func" << endl;
	//return (l2.Time - l1.Time)*24*3600;
    double t1, t2;
    double time;
    t1 = GetTime(l1.Time);
    t2 = GetTime(l2.Time);
    time = t2-t1;
    if(time < 0)
        time = time + 24*60*60;
    //cout << "time between: " << time << endl;
    return time;
}

double distance(double &lat1, double &lon1, double &lat2, double &lon2)
// double distance(GPSlog log1, GPSlog log2)
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

string getdate(string s)
{
	int pos1, pos2;
	pos1 = pos2 = 0;
	for(int i = 0; i < 4; i++)
	{
		pos1 = s.find_first_of(',', pos1);
		pos1++;
	}
	pos2 = s.find_first_of('.', pos1);
	// printf("%d, %d\n", pos1, pos2);
	return s.substr(pos1, pos2 - pos1);
}

void ReadTraj(string input, vector <GPSlog> & traj)
{
    FILE *fp = fopen(input.c_str(), "r");

    double lat, lng;
    char time[20];
    GPSlog point;
    string t;
    while(fscanf(fp, "%lf %lf %s\n", &lat, &lng, time) != EOF)
    {
        point.Latitude = lat;
        point.Longitude = lng;
        t = string(time);
        point.Time = t;
        traj.push_back(point);
    }
    return;
}

void DetectRegion(double D, double T, double Time, vector <GPSlog> & traj, vector <int> & StartIndex, vector <int> &EndIndex )
{
    StartIndex.push_back(0);
    int i = 0;
    int m, start;
    int size = traj.size();
    double Time_sec = Time*60;
    double TimeGap;
/*
    for(i = 0; i < size-1; i++)
    {
        TimeGap = timebetween(traj[i], traj[i+1]);
        if(TimeGap > Time_sec)
        {
            StartIndex.push_back(i+1);
            EndIndex.push_back(i);
        }
    }
*/
    //cout << "detect" << endl;
    start = 1;
	m = 0;
    while(m < size)
	{
		/*find the index startindex that satisfy the time threshold*/
		//cout << m << endl;
		while(start < size && (timebetween(traj[m], traj[start]) < T*60) )
		{
			start++;
		}
		//cout << "a time "  <<m <<" " << start<< endl;
		/*check if all the points satisfy the distance threshold*/
		i = start-1;
		while((distance(traj[i].Latitude, traj[i].Longitude, traj[m].Latitude, traj[m].Longitude) <= D) && i > m )
			i--;

		if(i == m + 1 && (timebetween(traj[m], traj[start]) >= T*60))
		{
            cout << "detect a region" << endl;
			/*if all the points satisfy the distance,increase startindex to find the first index that un-satisfy*/
			start++;
			while(start < size &&(distance(traj[start].Latitude, traj[start].Longitude, traj[m].Latitude, traj[m].Longitude) <= D))
				start++;
			//start--;

           // cout << "start: " << m << endl;
            //cout << "end: " << start << endl;
			EndIndex.push_back(m);
			StartIndex.push_back(start);

			m = start;
			start = m+1;
		}
		else
		{
			m++;
		}
		//cout << "ok " << endl;
	}
   // cout << "here" << endl;
	EndIndex.push_back(size-1);
}

int main(int argc, char * argv[])
{
    string input = argv[1];
    double D = atof(argv[2]);
    double T = atof(argv[3]);
    double Time = atof(argv[4]);
    vector <int> StartIndex;
    vector <int> EndIndex;
    vector <GPSlog> traj;
    int parts;
    string output, filename;
    int i;
    char a = '1';
    int fstart, fend;

    ReadTraj(input, traj);
    DetectRegion(D, T, Time, traj, StartIndex, EndIndex);

    cout << "begin to write" << endl;
    parts = StartIndex.size();
    cout << "There is(are)  " << parts << " part(s) in this trajectory" << endl;

    fstart = input.find_last_of('/');
    fend = input.find_last_of('.');
    //cout << fstart << " " << fend << endl;
    filename = input.substr(fstart, fend-fstart);
    cout << filename << endl;
/*
    //split one trajectory into several trajectories
    for(i = 0; i < parts; i++)
    {
        output = "./trajectory" + filename +"_" + a + ".txt";
        cout << output<< endl;
        FILE *fp = fopen(output.c_str(), "w");

        for(int j = StartIndex[i]; j < EndIndex[i]; j++)
        {
            fprintf(fp, "%lf %lf %s\n", traj[j].Latitude, traj[j].Longitude, traj[j].Time.c_str());
        }
        a++;
    }
    */
    //still in one trajectory file, but delete the stay regions.
    output = "./trajectory" + filename + ".txt";
    FILE *fp = fopen(output.c_str(), "w");
    for(i = 0; i < parts; i++)
    {
        for(int j = StartIndex[i]; j < EndIndex[i]; j++)
                fprintf(fp, "%lf %lf %s\n", traj[j].Latitude, traj[j].Longitude, traj[j].Time.c_str());
    }


}
