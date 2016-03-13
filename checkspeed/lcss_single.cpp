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
	double epsilon = atof(argv[2]);
	double latitude, longitude;
	char temp[20];
	double dist;
	vector <GPSPoint> query, cant, newcant;
	GPSPoint point;
	int m, n, i, j, k;
//	m = n = 120;
	int *lcs, *newlcs;
	double oldavg(0), newavg(0);

	string queryfile = "../Data/newtrajectory/" + to_string(tid);
	string cantsfile = "./" + to_string(tid) + "_cant.txt";

	vector <int> cantid;
	fp1 = fopen(cantsfile.c_str(), "r");
	while(fscanf(fp1, "%d\n", &i) != EOF)
		cantid.push_back(i);
	fclose(fp1);


	for(int s = 0; s < cantid.size(); s++)
	{

	string oldfile, newfile;
	oldfile = "../Data/newtrajectory/" + to_string(cantid[s]);
	newfile = "./" + to_string(tid) + "new/new" + to_string(cantid[s]);


	fp1 = fopen(queryfile.c_str(), "r");
	fp2 = fopen(oldfile.c_str(), "r");
	fp3 = fopen(newfile.c_str(), "r");

	query.erase(query.begin(), query.end());
	cant.erase(cant.begin(), cant.end());
	newcant.erase(newcant.begin(), newcant.end());


	cout << "begin to read" << endl;
	i = j = k = 0;
	while(fscanf(fp1, "%lf %lf %s\n", &point.lat, &point.lng, temp) != EOF)
	{
		query.push_back(point);
		i++;
	}
	m = i;

	while(fscanf(fp2, "%lf %lf %s\n", &point.lat, &point.lng, temp) != EOF)
	{
		cant.push_back(point);
		j++;
	//	cout << j << endl;
	}
	n = j;
	// cout  << i << " " << j << endl;

	while(fscanf(fp3, "%lf %lf %s\n", &point.lat, &point.lng, temp) != EOF)
	{
		newcant.push_back(point);
		k++;
	}

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	lcs = new int [(m+1)*(n+1)];
	newlcs = new int [(m+1)*(k+1)];

	for(i = 1; i <= m; i++)
		lcs[i*(n+1)] = 0;
	for(j = 0; j <= n; j++)
		lcs[j] = 0;

	for(i = 1; i <= m; i++)
		newlcs[i*(k+1)] = 0;
	for(j = 0; j <= k; j++)
		newlcs[j] = 0;

	int delta = max(m,n);
	int newdelta = max(m,k);
	for(i = 1; i <= m; i++)
	{
		for(j = 1; j <= n; j++)
		{

			dist = distance(query[i].lat, query[i].lng, cant[j].lat, cant[j].lng);
			//cout << i << " " << j << " " << dist << endl;
			if(dist <= epsilon && abs(m-n) <= delta)
			{
				/*cout << i << " " << j << endl;
				cout << "query: " << query[i].lat << " " << query[i].lng << endl;
				cout << "cant: " << cant[j].lat << " " << cant[j].lng << endl;
				cout << "distance : " << dist << endl; */
				lcs[i*(n+1)+j] = lcs[(i-1)*(n+1) + (j-1)] + 1;
			}
			else
			{
				lcs[i*(n+1)+j] = max(lcs[(i-1)*(n+1) + j], lcs[i*(n+1) + j - 1]);
			}
		}
	}

	for(i = 1; i <= m; i++)
	{
		for(j = 1; j <= k; j++)
		{

			dist = distance(query[i].lat, query[i].lng, newcant[j].lat, newcant[j].lng);
			//cout << i << " " << j << " " << dist << endl;
			if(dist <= epsilon && abs(i-j) <= newdelta)
			{
				/*cout << i << " " << j << endl;
				cout << "query: " << query[i].lat << " " << query[i].lng << endl;
				cout << "cant: " << cant[j].lat << " " << cant[j].lng << endl;
				cout << "distance : " << dist << endl; */
				newlcs[i*(k+1)+j] = newlcs[(i-1)*(k+1) + (j-1)] + 1;
			}
			else
			{
				newlcs[i*(k+1)+j] = max(newlcs[(i-1)*(k+1) + j], newlcs[i*(k+1) + j - 1]);
			}
		}
	}



	double rate = (double)lcs[(m+1)*(n+1)-1]/m; 
	double newrate = (double)newlcs[(m+1)*(k+1)-1]/m;
	cout << "*****" << cantid[s] << "*****" << endl;
	cout << lcs[(m+1)*(n+1)-1] << " " << rate << endl;
	cout << newlcs[(m+1)*(k+1)-1] << " " << newrate << endl;
	newavg += newrate;
	oldavg += rate;
	}

	newavg = newavg/cantid.size();
	oldavg = oldavg/cantid.size();
	cout << "old average is " << oldavg << endl;
	cout << "new average is " << newavg << endl;
	
	return 0;
}
