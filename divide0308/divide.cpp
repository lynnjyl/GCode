
/*divide the trajectory into several parts, each part is 10 minutes long;*/
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
	double lat, lng, time;
	char temp[20];
	string timestr;
	vector <GPSpoint> traj;
	GPSpoint p;

// cout << "in" << endl;
	int p1, p2;
	int hour, min, sec;
	while(fscanf(file, "%lf %lf %lf\n", &lat, &lng, &time) != EOF)
	{
		p.lat = lat;
		p.lng = lng;

		/*timestr = string(temp);
		//cout << timestr << endl;
		p1 = timestr.find_first_of(":", 0);
		hour = atoi(timestr.substr(0, p1).c_str());
		p2 = timestr.find_first_of(":", p1+1);
		min = atoi(timestr.substr(p1+1, p2-p1).c_str());
		sec = atoi(timestr.substr(p2+1, timestr.length()).c_str());*/
		
		// p.time = hour*3600 + min*60 + sec;
		p.time = time;
		// cout <<time << endl;
		traj.push_back(p);
	}
	fclose(file);
	traj.resize(traj.size());
	//cout << "here" << endl;
	return traj;
}

int main(int argc, char *argv[])
{
	//cout << "here" << endl;
	string file = argv[1];
	string filename = "../Data/traj0308/" + file;
	vector <GPSpoint> traj = GetTraj(filename);

	//cout << "ok" << endl;
	//cout << traj[traj.size()-1].time << endl;
	//cout << traj.begin()->time << endl;

	//double tdiff = traj[traj.size()-1].time - traj.begin()->time;
	int timediff = traj[traj.size()-1].time - traj.begin()->time;
	//cout << timediff << endl;
	if(timediff < 0)
		timediff += 86400;
	int segtime = 600;
	// cout << timediff << endl;

	int times = timediff/segtime;
	int remain = timediff%segtime;
	cout << file << endl;
	cout << times << " " << remain << endl;
	cout << timediff << endl;

	int i(0);
	double start = traj[0].time;
	vector <int> index;
	//cout << traj.size() << endl;
	for(i = 0; i < traj.size(); i++)
	{
		timediff = traj[i].time - start;
		//cout << i << " " << timediff << endl;
		if(timediff < 0)
			timediff += 86400;
		if(timediff > 600)
		{
			index.push_back(i-1);
			//cout << ">600 " << i << endl;
			start = traj[i-1].time;
		}
	}
	index.push_back(traj.size()-1);

	// cout << index.size() << endl;

	string output;
	FILE *fp;
	int j = 0;
	for(i = 0; i < times; i++)
	{
		output = "../Data/traj030802/" + file + to_string(i);
		fp = fopen(output.c_str(), "w");
		//cout << j << " " << index[i] << endl;
		//cout << traj[j].time << " " << traj[index[i]].time << endl;
		for(j; j <= index[i]; j++)
			fprintf(fp, "%lf %lf %d\n", traj[j].lat, traj[j].lng, int(traj[j].time));
		j = index[i];
		fclose(fp);
	}

	int size = traj.size();
	size--;

	if(remain > 300 && times > 0)
	{
		timediff = traj[size].time - traj[j].time;
		if(timediff < 0)
			timediff += 86400;
		while(timediff < 600)
		{
			j--;
			timediff = traj[size].time - traj[j].time;
			if(timediff < 0)
				timediff += 86400;
		}
		//cout << timediff << endl;

		output = "../Data/traj030802/" + file + to_string(i);
		fp = fopen(output.c_str(), "w");
		for(j; j <= size; j++)
			fprintf(fp, "%lf %lf %d\n", traj[j].lat, traj[j].lng, int(traj[j].time));
		fclose(fp);
	}

	






	return 0;
}