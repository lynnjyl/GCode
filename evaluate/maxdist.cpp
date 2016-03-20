#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;

struct GPSpoint
{
	double lat, lng;
};

#define pi 3.14159265358979323846
//string file1 = "00020081023025304.plt";
//string file2 = "00020090413213935.plt";


double deg2rad(double deg)
{
	return (deg * pi / 180);
}

double rad2deg(double rad)
{
	return (rad * 180 / pi);
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

	if(lat1 == lat2 && lon1 == lon2)
		return 0;
	else
		return (dist);
}

int main(int argc, char * argv[])
{
	/**************************************************/
	/*get all the index of the cant trajecotry: idlist*/
	int id = 89;
	string cfile = "../gm/cosine/result/" + to_string(id) +"_cosine_sort";
	vector <int> idlist;
	FILE *fp = fopen(cfile.c_str(), "r");

	int index;
	double val;

	fscanf(fp, "%d %lf\n", &index, &val);
	while(val >= 0.7)
	{
		idlist.push_back(index);
		fscanf(fp, "%d %lf\n", &index, &val);
	}
	fclose(fp);
	/*************************************************/
	cout << "stage one finished" << endl;

	//double lat, lng;
	vector <GPSpoint> query, cant;
	GPSpoint temp;
	int t, traj;
	string queryfile, cantfile;
	double min(200000), max(0), dist;
	/*************************************************/
	// read the original query file
	queryfile = "../Data/new/" + to_string(id);
	fp = fopen(queryfile.c_str(), "r");

	while(fscanf(fp, "%lf %lf %d\n", &temp.lat, &temp.lng, &t) != EOF)
	{
		query.push_back(temp);
	}
	query.resize(query.size());
	fclose(fp);
	/*************************************************/
	cout << "stage two finished" << endl;

	/*************************************************/
	// read the original candidate file
	traj = idlist[2];
	for(int k = 0; k < idlist.size(); k++)
	{
		traj = idlist[k];
		cantfile = "../Data/new/" + to_string(traj);
		fp = fopen(cantfile.c_str(), "r");
		while(fscanf(fp, "%lf %lf %d\n", &temp.lat, &temp.lng, &t) != EOF)
		{
			cant.push_back(temp);
		}
		fclose(fp);
		cout << "stage three finished" << endl;

		for(int i = 0; i < query.size(); i++)
		{
			for(int j = 0; j < cant.size(); j++)
			{
				dist = distance(query[i].lat, query[i].lng, cant[j].lat, cant[j].lng);
			// if(i == 2)
			// 	cout << j << " " << dist << endl;
				if(dist < min)
					min = dist;
			}
			//cout  << i <<  "min distance is " << min << endl;
			if(min > max)
				max = min;
			min = 2000000000;
		}
	// cout << "stage one finished" << endl;
	
		cout << "distance between " << id << " and " << traj << " is " << max << endl; 
		cant.erase(cant.begin(), cant.end());
		max = 0;
	}

	/*************************************************/






	return 0;
}