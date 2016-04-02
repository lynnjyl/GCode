#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
		
	int traj;
	vector <int>trajid;
	FILE *fp;

	/*fp = fopen("./query.txt", "r");
	int a, b;
	while(fscanf(fp, "%d %d\n", &a, &b) != EOF)
	{
		trajid.push_back(a);
	}
	fclose(fp);*/


	string filename;
	double lat, lng, time;
	double maxlat(0), maxlng(0);
	double minlat(10000), minlng(10000);
	
	for(int i = 1; i < 58182; i++)
	{
		// traj = trajid[i];
		traj = i;
	filename = "../Data/new/" + to_string(traj);

	fp = fopen(filename.c_str(), "r");
	//cout << filename << endl;

	
	//cout << "ok" << endl;
	while(fscanf(fp, "%lf %lf %lf\n", &lat, &lng, &time) != EOF)
	{
		//cout << lat << " " << lng <<endl;
		if(lat > maxlat)
			maxlat = lat;
		else
			if(lat < minlat)
				minlat = lat;
		if(lng > maxlng)
			maxlng = lng;
		else
			if(lng < minlng)
				minlng = lng;
	} 

	if((maxlat - minlat) < 0.002 || (maxlng - minlng) < 0.002)
		cout << traj << endl;
	
	maxlat = maxlng = 0;
	minlat = minlng = 10000;
	fclose(fp);

	}

	return 0;
}