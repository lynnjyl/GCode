#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <math.h>

using namespace std;

struct GPSPoint
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
	return (dist);
}

int main(int argc, char *argv[])
{
	FILE *fp1, *fp2, *fp3;

	/*fp1 = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "r");
	int tid = atoi(argv[3]);
	int delta = atoi(argv[4]);*/
	int tid = atoi(argv[1]);
	int trajid = atoi(argv[2]);
	double epsilon = atof(argv[3]);
	double latitude, longitude;
	double temp;
	double dist;
	vector <GPSPoint> query, cant, newcant;
	GPSPoint point;
	int m, n, i, j, k;
//	m = n = 120;
	int *lcs, *newlcs;
	double oldavg(0), newavg(0);

	string queryfile = "../Data/new/" + to_string(tid);
	string cantfile = "../Data/new/" + to_string(trajid);

	// vector <int> cantid;
	// fp1 = fopen(cantsfile.c_str(), "r");
	// while(fscanf(fp1, "%d\n", &i) != EOF)
	// 	cantid.push_back(i);
	// fclose(fp1)

	fp1 = fopen(queryfile.c_str(), "r");
	fp2 = fopen(cantfile.c_str(), "r");


	cout << "begin to read" << endl;
	i = j = k = 0;
	while(fscanf(fp1, "%lf %lf %lf\n", &point.lat, &point.lng, &temp) != EOF)
	{
		query.push_back(point);
		i++;
	}
	m = i;

	while(fscanf(fp2, "%lf %lf %lf\n", &point.lat, &point.lng, &temp) != EOF)
	{
		cant.push_back(point);
		j++;
	//	cout << j << endl;
	}
	n = j;
	cout << "length of query trajectory is " << m << endl;
	cout << "length of cantdidate trajectory is  " << n << endl;
	fclose(fp1);
	fclose(fp2);

	lcs = new int [(m+1)*(n+1)];
	newlcs = new int [(m+1)*(k+1)];

	for(i = 1; i <= m; i++)
		lcs[i*(n+1)] = 0;
	for(j = 0; j <= n; j++)
		lcs[j] = 0;

	// for(i = 1; i <= m; i++)
	// 	newlcs[i*(k+1)] = 0;
	// for(j = 0; j <= k; j++)
	// 	newlcs[j] = 0;

	int delta = max(m,n);
	// int newdelta = max(m,k);
	for(i = 1; i <= m; i++)
	{
		for(j = 1; j <= n; j++)
		{

			dist = distance(query[i].lat, query[i].lng, cant[j].lat, cant[j].lng);
			//cout << i << " " << j << " " << dist << endl;
			if(dist <= epsilon && abs(m-n) <= delta)
			{
				cout << i << " " << j << endl;
				cout << "query: " << query[i].lat << " " << query[i].lng << endl;
				cout << "cant: " << cant[j].lat << " " << cant[j].lng << endl;
				cout << "distance : " << dist << endl; 
				// cout << i << " " << j << " " << dist << endl;
				lcs[i*(n+1)+j] = lcs[(i-1)*(n+1) + (j-1)] + 1;
			}
			else
			{
				lcs[i*(n+1)+j] = max(lcs[(i-1)*(n+1) + j], lcs[i*(n+1) + j - 1]);
			}
		}
	}



	double rate = (double)lcs[(m+1)*(n+1)-1]/m; 
	// double newrate = (double)newlcs[(m+1)*(k+1)-1]/m;
	cout << "*****" << trajid << "*****" << endl;
	cout << lcs[(m+1)*(n+1)-1] << " " << rate << endl;
	// cout << newlcs[(m+1)*(k+1)-1] << " " << newrate << endl;
	
	

	
	
	return 0;
}
