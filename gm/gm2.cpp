/*
	use the distance from the GPS point to the grid center to get the weight value.

*/


#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <functional>
#include <stdlib.h>

using namespace std;


struct GPSpoint
{
	double lat;
	double lng;
};

// six circle of Beijing
double minlat = 39.688;
double minlng = 116.093;
double maxlat = 40.178;
double maxlng = 116.708;
double differ = 0.0005;
int lat_num = (maxlat - minlat)/differ + 1;
int lng_num = (maxlng - minlng)/differ + 1;
int size = int(lat_num * lng_num) + 1;


double edist(double lat1, double lng1, double lat2, double lng2)
{
	double a = lat2 - lat1;
	double b = lng2 - lng1;

	return sqrt(a*a + b*b);
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


int main(int argc, char * argv[])
{
	GPSpoint nw, ne, sw, se;
	double *GridWeight = new double[size];
	cout << "There are " << size << " grids." << endl;
	fill_n(GridWeight, size, 0);
	double lat, lng, lat_differ, lng_differ, differ_temp, cornerdiffer;
	char time[20];
	int lat_id, lng_id, grid_id;
	int grid_temp, i;
	//double dist, value;
	double dist, value[4], sum;
	GPSpoint centers[4];			// the 9 related grids.
	int centersid[4];
	//string filename = "../result/00020081023025304.plt";
	bool flag1, flag2;
	flag1 = flag2 = false;
	int trajid = atoi(argv[1]);
	string filename = argv[2];
	FILE * fp = fopen(filename.c_str(), "r");
	cout << trajid << " " << filename <<  endl;
	cornerdiffer = sqrt(differ*differ*2);


	//cout << lat_num << " " << lng_num << endl;
	int counter = 1;
	//int a;
	//cout << GridWeight[1] << endl;
	while(fscanf(fp, "%lf %lf %s\n", &lat, &lng, time) != EOF)
	{
		//fscanf(fp, "%lf %lf %s\n", &lat, &lng, time);
		sum = 0;
		lat_id = floor((lat - minlat)/differ);
		lng_id = ceil((lng - minlng)/differ);
		grid_id = lat_id*lng_num + lng_id;		//Id of the grid which the GPS point is in.

		//cout << lat << " " << lng << endl;
		//cout << lat_id << " " << lng_id << " " << grid_id << endl;


		centers[0].lat =  minlat + differ * (lat_id - 1) + differ/2;
		centers[0].lng = minlng + differ * (lng_id -1) + differ/2;
		centersid[0] = grid_id;

		//cout << "centers[0]: " << centersid[0] << " " << centers[0].lat << " " << centers[0].lng << endl;

		centers[1].lng = centers[0].lng;
		if(lat > centers[0].lat)
		{
			centers[1].lat = centers[0].lat + differ;
			centersid[1] = grid_id + lng_num;
		}
		else
		{
			centers[1].lat = centers[0].lat - differ;
			centersid[1] = grid_id - lng_num;
		}
		//cout << "centers[1]: " << centersid[1] << " " << centers[1].lat << " " << centers[1].lng << endl;

		centers[2].lat = centers[0].lat;
		if(lng > centers[0].lng)
		{
			centers[2].lng = centers[0].lng + differ;
			centersid[2] = grid_id +1;
		}	
		else
		{
			centers[2].lng = centers[0].lng - differ;
			centersid[2] = grid_id -1;
		}
		//cout << "centers[2]: " << centersid[2] << " " << centers[2].lat << " " << centers[2].lng << endl;


		centers[3].lat = centers[1].lat;
		centers[3].lng = centers[2].lng;
		//centersid[3] = floor((centers[3].lat - minlat)/differ)*lng_num + ceil((centers[3].lng - minlng)/differ);
		if(centersid[2] > centersid[0])
			centersid[3] = centersid[1] + 1;
		else
			centersid[3] = centersid[1] - 1;
		//cout << "centers[3]: " << centersid[3] << " " << centers[3].lat << " " << centers[3].lng << endl;

		for(i = 0; i < 4; i++)
		{
			dist = distance(lat, lng, centers[i].lat, centers[i].lng);
			value[i] = 1/dist;
			sum += value[i];
		}

		for(i = 0; i < 4; i++)
		{
			value[i] = value[i]/sum;
			if(centersid[i] > 0 && centersid[i] < size)
				GridWeight[centersid[i]] = max(value[i], GridWeight[centersid[i]]);
		}


		//cin >> a;

		/*//calculate the 9 grids related to the GPS point.
		//the center, index = 4;
		centers[4].lat = minlat + differ * (lat_id - 1) + differ/2;
		centers[4].lng = minlng + differ * (lng_id -1) + differ/2;

		centers[0].lat = centers[1].lat = centers[2].lat = centers[4].lat + differ;
		centers[3].lat = centers[5].lat = centers[4].lat;
		centers[6].lat = centers[7].lat = centers[8].lat = centers[4].lat - differ;
		
		centers[0].lng = centers[3].lng = centers[6].lng = centers[4].lng - differ;
		centers[1].lng = centers[7].lng = centers[4].lng;		
		centers[2].lng = centers[5].lng = centers[8].lng = centers[4].lng + differ;

		//get the ids of the grids related.
		centersid[4] = grid_id;

		centersid[1] = grid_id + lng_num;
		centersid[7] = grid_id - lng_num;
		centersid[3] = grid_id -1;
		centersid[5] = grid_id +1;

		centersid[0] = centersid[1] - 1;
		centersid[2] = centersid[1] + 1;
		centersid[6] = centersid[7] - 1;
		centersid[8] = centersid[7] + 1;		
		
		//get the weight value based on the distance;
		for(i = 0; i < 9; i++)
		{
			dist = distance(centers[i].lat, centers[i].lng, lat, lng);
			value = 1/dist;
			if(centersid[i] > 0 && centersid[i] < size)
				GridWeight[centersid[i]] = max(value, GridWeight[centersid[i]]);
		}*/
	}
	fclose(fp);

	fp = fopen("matrix_sub_gm_2.txt", "a");
	for(int i = 0; i < size; i++)
	{
		if(GridWeight[i] != 0)
			fprintf(fp, "%d %d %lf\n", trajid, i, GridWeight[i]);
	}

	return 0;
}