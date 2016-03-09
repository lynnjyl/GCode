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
	FILE *fp1, *fp2;

	fp1 = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "r");
	int tid = atoi(argv[3]);
	int delta = atoi(argv[4]);
	double epsilon = atof(argv[5]);
	double latitude, longitude;
	char temp[20];
	double dist;
	vector <GPSPoint> query, cant;
	GPSPoint point;
	int m, n, i, j;
//	m = n = 120;
	int *lcs;

/*

	for(i = 0; i < m; i++)
	{
		fscanf(fp1, "%lf %lf %s", &point.lat, &point.lng, temp);
		query.push_back(point);
		fscanf(fp2, "%lf %lf %s", &point.lat, &point.lng, temp);
		cant.push_back(point);
	}
*/

//	cout << "begin to read" << endl;
	i = j = 0;
	while(fscanf(fp1, "%lf %lf %s\n", &point.lat, &point.lng, temp) != EOF)
	{
		query.push_back(point);
		i++;
	}
	m = i;

//	cout << "ok" << endl;
	while(fscanf(fp2, "%lf %lf %s\n", &point.lat, &point.lng, temp) != EOF)
	{
		cant.push_back(point);
		j++;
	//	cout << j << endl;
	}
	n = j;

	fclose(fp1);
	fclose(fp2);
	lcs = new int [(m+1)*(n+1)];

	for(i = 1; i <= m; i++)
		lcs[i*(n+1)] = 0;
	for(j = 0; j <= n; j++)
		lcs[j] = 0;


	for(i = 1; i <= m; i++)
	{
		for(j = 1; j <= n; j++)
		{

			dist = distance(query[i].lat, query[i].lng, cant[j].lat, cant[j].lng);
			//cout << i << " " << j << " " << dist << endl;
			if(dist <= epsilon && abs(m-n) <= delta)
			{
			//	cout << i << " " << j << endl;
			//	cout << "query: " << query[i].lat << " " << query[i].lng << endl;
			//	cout << "cant: " << cant[j].lat << " " << cant[j].lng << endl;
			//	cout << "distance : " << dist << endl; 
				lcs[i*(n+1)+j] = lcs[(i-1)*(n+1) + (j-1)] + 1;
			}
			else
			{
				lcs[i*(n+1)+j] = max(lcs[(i-1)*(n+1) + j], lcs[i*(n+1) + j - 1]);
			}
		}
	}
/*
	for(i = 1; i <= m; i++)
	{
		for(j = 1; j <= n; j++)
		{
			cout<< lcs[i*(n+1)+j] << " ";
		}
		cout << endl;
	}
*/




	string queryfile = argv[1];
	int k = queryfile.find_last_of("/");
	k++;
	string name = queryfile.substr(k, queryfile.length()-k);

	string cantfile = argv[2];
	k = cantfile.find_last_of("/");
	k++;
	string name2 = cantfile.substr(k, cantfile.length()-k);
//	cout << name << endl;

	string output = "./result/lcss_" + name; 
	fp1 = fopen(output.c_str(), "a");
//	cout << lcs[(m+1)*(n+1)-1] << endl;
	double rate = (double)lcs[(m+1)*(n+1)-1]/120; 
//	fprintf(fp1, "%d\n", tid);
	fprintf(fp1, "%s %d %lf\n", name2.c_str(), lcs[(m+1)*(n+1)-1], rate);
//	cout << "i" << endl;
//	cout << lcs[(m+1)*(n+1)-1] << " " << rate << endl;
	
	
	return 0;
}
