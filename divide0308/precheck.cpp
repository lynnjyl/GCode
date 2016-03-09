#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;
struct GPSpoint
{
	double lat, lng, time;
};


vector <GPSpoint> GetTraj(string filename)
{
	FILE *file = fopen(filename.c_str(), "r");
	double lat, lng;
	char temp[20];
	string timestr;
	vector <GPSpoint> traj;
	GPSpoint p;

	int p1, p2;
	int hour, min, sec;
	while(fscanf(file, "%lf %lf %s\n", &lat, &lng, temp) != EOF)
	{
		p.lat = lat;
		p.lng = lng;

		timestr = string(temp);
		//cout << timestr << endl;
		p1 = timestr.find_first_of(":", 0);
		hour = atoi(timestr.substr(0, p1).c_str());
		p2 = timestr.find_first_of(":", p1+1);
		min = atoi(timestr.substr(p1+1, p2-p1).c_str());
		sec = atoi(timestr.substr(p2+1, timestr.length()).c_str());
		
		p.time = hour*3600 + min*60 + sec;
		traj.push_back(p);
	}
	fclose(file);
	traj.resize(traj.size());
	return traj;
}

int main(int argc, char *argv[])
{
	string file = argv[1];
	string fileindex = file.substr(0, file.length()-4);
	cout << fileindex << endl;
	string filename = "../Data/trajectory/" + file;
	vector <GPSpoint> traj = GetTraj(filename);

	int timediff = traj[traj.size()-1].time - traj.begin()->time;
	cout << timediff << endl;
	int diff;
	vector <int> index;
	index.push_back(0);
	int i;
	//int segtime = 600;

	for(i = 1; i < traj.size(); i++)
	{
		diff = traj[i].time - traj[i-1].time;
		if(diff < 0)
			diff = diff + 86400;
		if(diff > 120)
		{
			//lcout << diff << endl;
			index.push_back(i);
		}
	}
	index.push_back(traj.size());

	FILE *fp;
	string fname;
	cout << index.size() << endl;

	for(i = 0; i < index.size()-1; i++)
	{
		fname = "../Data/traj0308/" + fileindex + "_" + to_string(i);
		fp = fopen(fname.c_str(),"w");
		for(int j = index[i]; j < index[i+1]; j++)
			fprintf(fp, "%lf %lf %lf\n", traj[j].lat, traj[j].lng, traj[j].time);
		fclose(fp);
	}
	//cout << "i" << endl;
	return 0;
}