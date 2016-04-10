#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <math.h>
#include <sys/time.h>
#include <ctime>
using namespace std;

struct GPSPoint
{
	double lat, lng;
};

double wallclock(void)
{
	struct  timeval tv;
	struct  timezone tz;
	double t;
	gettimeofday(&tv, &tz);
	t = (double)tv.tv_sec*1000;
	t += ((double)tv.tv_usec)/1000;
	return t;
}

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

//	fp1 = fopen(argv[1], "r");
//	fp2 = fopen(argv[2], "r");
	
	srand((unsigned)time(0));
	//int tid = atoi(argv[1]);
	int tid;
	int delta = atoi(argv[1]);
	double epsilon = atof(argv[2]);
	int count = atoi(argv[3]);
	double latitude, longitude;
	char temp[20];
	double dist;
	vector <GPSPoint> query, cant;
	GPSPoint point;
	int m, n, i(0), j(0);
	int *lcs;
	
	string queryfile, cantfile;

	double t1, t2, tsum(0);

	int num = count;
	while(count > 0)
	{
		tid = rand()%58181 + 1;
		queryfile = "../Data/new/" + to_string(tid);
		fp1 = fopen(queryfile.c_str(), "r");
		while(fscanf(fp1, "%lf %lf %s\n", &point.lat, &point.lng, temp) != EOF)
		{
			query.push_back(point);
			i++;
		}
		m = i;
		fclose(fp1);

		


		for(int k = 1; k <= 58181; k++)
		{
			cantfile = "../Data/new/" + to_string(k);
			fp2 = fopen(cantfile.c_str(), "r");
			while(fscanf(fp2, "%lf %lf %s\n", &point.lat, &point.lng, temp) != EOF)
			{
				cant.push_back(point);
				j++;
			}
			fclose(fp2);
			n = j;
			t1 = wallclock();
			lcs = new int [(m+1)*(n+1)];

			for(i = 1; i <= m; i++)
				lcs[i*(n+1)] = 0;
			for(j = 0; j <= n; j++)
				lcs[j] = 0;


			for(i = 1; i <= m; i++)
			{
				for(j = 1; j <= n; j++)
				{
					if(abs(i-j) <= delta)
					{
						dist = distance(query[i].lat, query[i].lng, cant[j].lat, cant[j].lng);
						if(dist <= epsilon)
							lcs[i*(n+1)+j] = lcs[(i-1)*(n+1) + (j-1)] + 1;
						else
							lcs[i*(n+1)+j] = max(lcs[(i-1)*(n+1) + j], lcs[i*(n+1) + j - 1]);
					}
				}
			}

			t2 = wallclock();
			tsum += t2 - t1;
			j = 0;
			delete []lcs;
		}
		count--;
	}

	cout << "lcss query time is :" << tsum/(double)num << endl;

	return 0;
}
