#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <math.h>

using namespace std;

struct GPSpoint
{
	double lat;
	double lng;
	double time;
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
	return (dist);
}

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
	return traj;
}

/*double distance(GPSpoint p1, GPSpoint p2)
{
	double dist = sqrt((p1.lat - p2.lat)*(p1.lat - p2.lat) + (p1.lng - p2.lng)*(p1.lng - p2.lng));
	return dist;
}*/

double GetSpeed(vector <GPSpoint> traj)
{
	double sum;
	double diff;
	int speed;
	int i;
	for(i = 1; i < traj.size(); i++)
	{
		diff = traj[i].time - traj[i-1].time;
		sum += diff;
	}

	speed = floor(sum/traj.size());
	return speed;
}

vector <GPSpoint> Addpoints(vector <GPSpoint> traj, int speed)
{
	int i, j;
	int diff;
	int times;
	double latdiff, lngdiff;
	GPSpoint ap;
	vector <GPSpoint> newtraj;

	for(i = 1; i < traj.size(); i++)
	{
		newtraj.push_back(traj[i-1]);
		diff = int(traj[i].time - traj[i-1].time);
		times = ceil(diff/speed);
		//cout << times << endl;

		latdiff = (traj[i].lat - traj[i-1].lat)/times;
		lngdiff = (traj[i].lng - traj[i-1].lng)/times;

		for(j = 1; j < times; j++)
		{
			ap.lat = traj[i-1].lat + j*latdiff;
			ap.lng = traj[i-1].lng + j*lngdiff;
			ap.time = traj[i-1].time + j*diff;

			newtraj.push_back(ap);
		}
		/*cout << "****" << i << "****" << endl;
		cout << times << endl;
		cout << newtraj.size() << endl;*/
	}


	newtraj.push_back(traj[i-1]);
	// cout << newtraj.size() << endl;
	return newtraj;
}

int main(int argc, char *argv[])
{
	FILE *fp1, *fp2, *fp3;
	fp1 =fopen(argv[1], "r");
	fp2 = fopen(argv[2], "r");
	int num1 = atoi(argv[3]);
	int num2 = atoi(argv[4]);
	string query = argv[5];
	//vector <int>::iterator it;
	int id, i, temp;
	double val;
	//vector <int> v1 ,v2, uni, inter;
	//set <int> uni, inter;
	set <int> s1, s2, uni, inter, differ1, differ2;
	char name[20];
	vector <GPSpoint> qt;
	vector <GPSpoint> ct;
	//string *p;
	//uni.resize(num1+num2);
	//inter.resize(num1+num2);


	//cout << "cosine" << endl;
	for(i = 0; i < num1; i++)
	{
		fscanf(fp1, "%d %lf\n", &id, &val);
		//cout << id << endl;
		s1.insert(id);
		//uni.insert(id);
	}
		//cout << "lcss" << endl; 

	for(i = 0; i < num2; i++)
	{
		fscanf(fp2, "%d %d %lf\n", &id, &temp, &val);
		s2.insert(id);
		//cout << id << endl;
		//uni.insert(id);
	}

	set_union(s1.begin(), s1.end(), s2.begin(), s2.end(),inserter(uni, uni.begin()));
	//set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(),inserter(differ, differ.begin()));
	set_intersection(s1.begin(),s1.end(),s2.begin(), s2.end(),inserter(inter,inter.begin()));


	cout << "*************Top " << num1 << "**************" << endl;
	cout << "union size        = " << uni.size() << endl;
	cout << "intersection size = " << inter.size() << endl;
	cout << "*******************************" << endl;

	//cout << inter.size() << endl;

	cout << "element appear in set1 but not in set2:" << endl;
	set_difference(s1.begin(), s1.end(), inter.begin(),inter.end(),inserter(differ1,differ1.begin()));
	for(auto k:differ1) cout << k << " ";
		cout << endl;

	cout << endl;
	cout << "element appear in set2 but not in set1:" << endl;
	set_difference(s2.begin(), s2.end(), inter.begin(),inter.end(),inserter(differ2,differ2.begin()));
	for(auto k:differ2) cout << k << " ";
		cout << endl;


	//string fileindex;
	string filename;
	string queryname = "../Data/newtrajectory/" + query;
	double qspd, cspd;
	qt = GetTraj(queryname);
	qspd = GetSpeed(qt);
	cout << "query speed  is " << qspd << endl;

	int cantindex;

	set <int>::iterator it;
	it = differ1.begin();
	while(it != differ1.end())
	{
		cantindex = *it;
		cout << cantindex << endl;
		filename = "../Data/newtrajectory/" + to_string(cantindex);
		cout << filename << endl;

		ct = GetTraj(filename);
		cout << ct.size() << endl;
		cspd = GetSpeed(ct);
		cout << "candidate speed is " << cspd << endl;

		vector <GPSpoint> newtraj = Addpoints(ct, floor(qspd));


		string newfile = "./" + query + "new/new" + to_string(cantindex);
		FILE *nf = fopen(newfile.c_str(), "w");
		for(i = 0; i < newtraj.size(); i++)
		{
			fprintf(nf, "%lf %lf %lf\n", newtraj[i].lat, newtraj[i].lng, newtraj[i].time);
		}
		fclose(nf);
		it++;

		newfile = argv[5];
		newfile = newfile + "_cant.txt";
		nf = fopen(newfile.c_str(), "w");
		for(auto k:differ1)
			fprintf(nf, "%d\n", k);
		fclose(nf);
	}
	/*for(auto k:differ1)
	{
		fileindex = to_string(k);
		//cout << fileindex << " ";
		filename = "../Data/newtrajectory/" + fileindex;
	}
	cout << endl;
*/


	return 0;
}
