#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#include <string.h>
#include <functional>


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
	FILE *fp = fopen(filename.c_str(), "r");
	//cout << filename << endl;
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

double DTW(vector<GPSpoint> traj1, vector<GPSpoint> traj2)
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
		dtw[i][0] = Edistance(traj1[i].lat, traj1[i].lng, traj2[0].lat, traj2[0].lng);
	for(i = 0; i < size2; i++)
		dtw[0][i] = Edistance(traj2[i].lat, traj2[i].lng, traj1[0].lat, traj1[0].lng);

	for(i = 1; i < size1; i++)
	{
		for(j = 1; j < size2; j++)
		{
			mm = min(min(dtw[i-1][j], dtw[i-1][j-1]), dtw[i][j-1]);
			dtw[i][j] = mm + Edistance(traj1[i].lat, traj1[i].lng, traj2[j].lat, traj2[j].lng);
			//cout << "dtw " << i << " " << j << ": " << dtw[i][j] << endl;
		}
	}
	return dtw[size1-1][size2-1];
}

void GetAllFilenames(/*vector <int> &fileids, */vector <string> &filenames)
{
	FILE *fp = fopen("index.txt", "r");
	char name[30];
	int id;

	while(fscanf(fp, "%d %c\n", &id, name) != EOF)
	{	
			//fileids.push_back(id);
			filenames.push_back(string(name));
	}
	return;
}

bool less_len(const candidate & c1, const candidate &c2)
{
	return c1.dist < c2.dist;
}

int main(int argc, char* argv[])
{
	FILE *fp = fopen("index.txt", "r");
	vector<GPSpoint> traj1;
	vector<GPSpoint> traj2;
	string queryfile = argv[1];
	vector <string> filenames;
	string name;
	//vector <int> fileids;
	double dist, max_dist;
	int num = atoi(argv[2]);
	candidate *cant = new candidate[num];
	candidate cant_temp;
	int i, j, id;
	char filename[30];

	cout << "begin to read" << endl;
	
	//GetAllFilenames(filenames);
	ReadFile(queryfile, traj1);

	cout << "read finished" << endl;

	for(i = 0; i < 18670; i++)
	{
		//cout << filenames[i] << endl;
		fscanf(fp, "%d %s\n", &id, filename);
		cout << filename << endl;

		if(string(filename) != queryfile)
		{	
			name = "../result/" + string(filename);
			
			cout << name << endl;
			ReadFile(name, traj2);
			dist = DTW(traj1, traj2);
			cout << dist << endl;
			cant_temp.id = i+1;
			cant_temp.dist = dist;
			if(i < num)
			{
				cant[i] = cant_temp;
			}
			else
			{
				sort(cant, cant+num, less_len);
				max_dist = cant[num-1].dist;

				if(dist < max_dist)
				{
					cant[num-1] = cant_temp;
				}
			}
			/*for(j = 0; j < num; j++)
				cout << cant[j].id << " " << cant[j].dist << endl;
			cout << "**************************" << endl;*/
			traj2.clear();
		}
	}

	string output = "candidateof" + queryfile;
	FILE *fp2 = fopen(output.c_str(), "w");

	for(j = 0; j < num; j++)
	{
		fprintf(fp2, "%d %lf\n", cant[j].id, cant[j].dist);
	}
	fclose(fp2);
	fclose(fp);

	
	//ReadFile(file2, traj2);

	//cout << "read finished" << endl;
	//dist = DTW(traj1, traj2);

	//cout << "Distance: " << dist << endl;




	return 0;
}