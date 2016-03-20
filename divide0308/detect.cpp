#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;


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


int main()
{
	int trajid = 1;
	double lat, lng, t;
	double minlat(130), maxlat(0);
	double minlng(130), maxlng(0);

	string filename;
	FILE *fp;
	double latdist, lngdist;
	double midlat;
	double midlng;



	for(trajid = 1; trajid < 58182; trajid++)
	{
		filename = "../Data/new/" + to_string(trajid);
		fp = fopen(filename.c_str(), "r");
		while(fscanf(fp, "%lf %lf %lf\n", &lat, &lng, &t) != EOF)
		{
			if(lat < minlat)
				minlat = lat;
			else
				if(lat > maxlat)
					maxlat = lat;

			if(lng < minlng)
				minlng = lng;
			else
				if(lng > maxlng)
					maxlng = lng;
		}
		fclose(fp);


		midlat = (minlat + maxlat)/2;
		midlng = (minlng + maxlng)/2;
		latdist = distance(minlat, midlng, maxlat, midlng);
		lngdist = distance(midlat, minlng, midlat, maxlng);
		//cout << latdist << " " << lngdist << endl;
		if(latdist < 100 && lngdist < 100)
			cout << trajid << endl;
		minlat = minlng = 130;
		maxlat = maxlng = 0;
	}





	return 0;
}