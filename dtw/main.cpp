#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#include <string.h>
#include <functional>
#include <set>

using namespace std;

struct GPSpoint
{
	double lat;
	double lng;
};

struct candidate
{
	int id;
	double dist;
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


void ReadFile(string filename, vector<GPSpoint> & traj)
{
	//cout << "in read file" << endl;
	FILE *fp = fopen(filename.c_str(), "r");
	cout << filename << endl;
	double latitude, longitude;
	char temp[50];
	GPSpoint p;
	while(fscanf(fp, "%lf %lf %s\n", &latitude, &longitude, temp) != EOF)
	{
		p.lat = latitude;
		p.lng = longitude;
		traj.push_back(p);
	}
	fclose(fp);
	return;
}

double Edistance(double lat1, double lng1, double lat2, double lng2)
{
	double a = lat1 - lat2;
	double b = lng1 - lng2;

	return sqrt(a*a + b*b);
}

double ** DTW(vector<GPSpoint> traj1, vector<GPSpoint> traj2)
{
	//cout << "begin dtw" << endl;
	int size1 = traj1.size();
	int size2 = traj2.size();
	int i, j;
	double mm;

	double **dtw = new double *[size1];
	for(i = 0; i < size1; i++)
		dtw[i] = new double[size2];

	
	for(i = 0; i < size1; i++)
		dtw[i][0] = distance(traj1[i].lat, traj1[i].lng, traj2[0].lat, traj2[0].lng);
	for(i = 0; i < size2; i++)
		dtw[0][i] = distance(traj2[i].lat, traj2[i].lng, traj1[0].lat, traj1[0].lng);

	for(i = 1; i < size1; i++)
	{
		for(j = 1; j < size2; j++)
		{
			dtw[i][j] = distance(traj1[i].lat, traj1[i].lng, traj2[j].lat, traj2[j].lng);
		}
	}

	return dtw;
}

void GetAllFilenames(/*vector <int> &fileids, */string *filenames)
{
	FILE *fp = fopen("index.txt", "r");
	char name[30];
	int id;

	//cout << "here" << endl;
	while(fscanf(fp, "%d %s\n", &id, name) != EOF)
	{	
			//fileids.push_back(id);
			//cout << name << endl;
			filenames[id] = string(name);
	}
	fclose(fp);
	return;
}

bool less_len(const candidate & c1, const candidate &c2)
{
	return c1.dist < c2.dist;
}

void GetAllCandidates(vector <int> &candid)
{
	FILE *fp = fopen("cant.txt", "r");
	int id;
	while(fscanf(fp, "%d\n", &id) != EOF)
		candid.push_back(id+1);			//LSH part id set from 0
	return;
}

double GetRate(double **dtw, int size1, int size2, double Thresdist)
{
	set <int> cants;
	for(int i = 0; i < size1; i++)
	{
		for (int j = 0; j < size2; j++)
		{
			if(dtw[i][j] < Thresdist)
			{
				//cout << i << " " << j << " " << dtw[i][j] << endl;
				cants.insert(i);
			}
		}
	}

	int num = cants.size();
	//cout << num << endl;
	//cout << size1 << endl;
	double rate = double(num)/double(size1);
	//cout << rate << endl;

	return rate;
}

int main(int argc, char* argv[])
{
	//FILE *fp = fopen("index.txt", "r");
	vector<GPSpoint> traj1;
	vector<GPSpoint> traj2;
	string queryfile = argv[1];			//	query file name
	string cantfile = argv[2];			//  file to be compared
	int tid = atoi(argv[3]);			// 	Trajectory ID
	double Thresdist = atof(argv[4]);
	//int mode = atoi(argv[4]);
	//vector <string> filenames;
	//string filenames[18671];
	string name;
	double **dtw;
	double rate;
	//vector <int> fileids;
	double dist/*, max_dist*/;
	int i;

	ReadFile(queryfile, traj1);

	int k = queryfile.find_last_of("/");
	k++;
	name = queryfile.substr(k, queryfile.length()-k);
	//cout << name << endl;

	string output = "./RateResult/candidate_" + name;
	//cout << output << endl;


	if(queryfile != cantfile)
	{
		ReadFile(cantfile, traj2);
		cout << "get distance" << endl;
		dtw = DTW(traj1, traj2);
		//cout << traj1[1].lat << " " << traj1[1].lng << endl;
		//cout << traj2[1].lat << " " << traj2[1].lng << endl;
		//cout << dtw[1][1] << endl;

		rate = GetRate(dtw, traj1.size(), traj2.size(), Thresdist);

		//cout << dist << endl;
		cout << rate << endl;
		
		FILE *fp2 = fopen(output.c_str(), "a");
		fprintf(fp2, "%d %lf\n", tid, rate);
		fclose(fp2);
	}




	return 0;
}
