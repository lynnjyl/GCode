#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

struct GPSpoint
{
	double lat, lng;
	int time;
};

int main(int argc,char *argv[])
{
	// int tid = atoi(argv[1]);

	string filename;
	FILE *fp;
	GPSpoint p;
	vector <GPSpoint> traj;
	int timediff;
	vector <GPSpoint>::iterator it;
	// int i(1);

// int tid = 6524;
	for(int tid = 1; tid <= 58181; tid++)
	{

		traj.erase(traj.begin(), traj.end());
		cout << tid <<endl;

	filename = "./newtraj/" + to_string(tid);
	fp = fopen(filename.c_str(), "r");
	

	while(fscanf(fp, "%lf %lf %d\n", &p.lat, &p.lng, &p.time) != EOF)
	{
		traj.push_back(p);
	}
	fclose(fp);

	// cout << "read finished" << endl;
	// int size = traj.size();

	it = traj.begin();
	// cout << it->lat << endl;
	
	while(it != traj.end()-2)
	{
		
		timediff = (it+2)->time - it->time;
		if(timediff < 0)
			timediff += 86400;
		// cout << "it time " << it->time << " it+2 time " << (it+2)->time << " timediff " << timediff << endl; 
		while(timediff <= 5)
		{
			traj.erase(it+1);
			// cout << "erase it+1" << endl;
			// cout << "now it+1 time " << (it+1)->time << endl;
			//cout << it->time << endl;
			//cout << traj.size() << endl;

			if((it+1) == traj.end())
			{
				// cout << "last" << endl;
				break;
			}
			timediff = (it+2)->time - it->time;
			// cout << "it time " << it->time << "it+2 time " << (it+2)->time << " timediff " << timediff << endl; 
			// cout << timediff << endl;
			if(timediff < 0)
				timediff += 86400;
		}
		it++;
		if(it == traj.end())
			break;
	}
	// cout << traj.size() << endl;
/*
	for(it = traj.begin(); it != traj.end(); it++)
		cout << it->lat << " " << it->lng << " " << it->time << endl;
	cout << "ok" << endl;*/

	filename = "./new/" + to_string(tid);
	fp = fopen(filename.c_str(), "w");
	for(it = traj.begin(); it != traj.end(); it++)
		fprintf(fp, "%lf %lf %d\n", it->lat, it->lng, it->time);

	fclose(fp);

	cout << "ok" << endl;

}




	return 0;
}