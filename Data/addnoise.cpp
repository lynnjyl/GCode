#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iomanip>

using namespace std;

struct GPSpoint
{
	double lat, lng;
	int time;
};

int main (int argc, char * argv[])
{
	int per = atoi(argv[1]);
	int trajid = atoi(argv[2]);

	string filename;
	FILE *fp;
	vector <GPSpoint> traj;
	GPSpoint tmp;
	int length, i, index;
	int tdiff, inst;
	/*double lat, lng;
	int time;*/
	setprecision(10);

	filename = "./new/" + to_string(trajid);
	fp = fopen(filename.c_str(), "r");

	while(fscanf(fp, "%lf %lf %d\n", &tmp.lat, &tmp.lng, &tmp.time) != EOF)
	{
		traj.push_back(tmp);
	}
	length = traj.size();
	fclose(fp);

	length=(int)(length*per/100);
	//cout << length << endl;

	for(i = 0; i < length; i++)
	{
		// cout<<setprecision(8)<<endl;
		//cout << "***************************" << endl;
		index = rand()%(traj.size()-1); //cout  << index << endl;
		tdiff = traj[index+1].time - traj[index].time; //cout << tdiff << endl;
		while(tdiff < 2)
		{
			index = rand()%(traj.size()-1);// cout  << index << endl;
			tdiff = traj[index+1].time - traj[index].time; //cout << tdiff << endl;
		}
		
		inst = rand()%(tdiff-1)+1;


		tmp.lat = (double)inst / (double)tdiff * (traj[index+1].lat - traj[index].lat) + traj[index].lat;
		tmp.lng = (double)inst / (double)tdiff * (traj[index+1].lng - traj[index].lng) + traj[index].lng;
		tmp.time = traj[index].time + inst;
		traj.insert(traj.begin()+index+1, tmp);
	}


	filename = "./new_" + to_string(per) + "/" + to_string(trajid);
	fp = fopen(filename.c_str(), "w");

	for(i = 0; i < traj.size(); i++)
		fprintf(fp, "%lf %lf %d\n", traj[i].lat, traj[i].lng, traj[i].time);

	fclose(fp);
	return 0;
}