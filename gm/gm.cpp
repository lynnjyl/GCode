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
	double dist, value;
	GPSpoint centers[9];			// the 9 related grids.
	int centersid[9];
	//string filename = "../result/00020081023025304.plt";
	int trajid = atoi(argv[1]);
	string filename = argv[2];
	FILE * fp = fopen(filename.c_str(), "r");
	cout << trajid << " " << filename <<  endl;
	cornerdiffer = sqrt(differ*differ*2);


	//cout << lat_num << " " << lng_num << endl;
	int counter = 1;

	//cout << GridWeight[1] << endl;
	while(fscanf(fp, "%lf %lf %s\n", &lat, &lng, time) != EOF)
	{
		//fscanf(fp, "%lf %lf %s\n", &lat, &lng, time);
		lat_id = floor((lat - minlat)/differ);
		lng_id = ceil((lng - minlng)/differ);
		grid_id = lat_id*lng_num + lng_id;		//Id of the grid which the GPS point is in.

		//calculate the 9 grids related to the GPS point.
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
		}





		/*GridWeight[grid_id] = 1;
		//cout <<counter << ": "  << lat_id << " " << lng_id << " " << grid_id << endl;
		//set four corner point
		ne.lat = nw.lat = (lat_id + 1) * differ + minlat;
		se.lng = ne.lng = (lng_id + 1) * differ + minlng;
		sw.lng = nw.lng = lng_id * differ + minlng;
		sw.lat = se.lat = lat_id * differ + minlat;

		//distance to the boundary
		// the northern side
		lat_differ = (lat_id + 1) * differ + minlat - lat;
		//cout << "lat_differ to the northern side " << lat_differ << endl;
		grid_temp = grid_id + lng_num;
		value = 1 - 2*lat_differ/differ;
		if(grid_temp < size & value > 0)
			GridWeight[grid_temp] = max(value, GridWeight[grid_temp]);
		//cout << grid_temp << " " << value << endl;


		// the southern side
		lat_differ = lat - (lat_id * differ + minlat);
		//cout << "lat_differ to the southern side " << lat_differ << endl;
		grid_temp = grid_id - lng_num;
		value = 1 - 2*lat_differ/differ;
		if(grid_temp > 0 & value > 0)
			GridWeight[grid_temp] = max(value, GridWeight[grid_temp]);
		//cout << grid_temp << " " << value << endl;


		// the western side
		lng_differ = lng - ((lng_id-1) *differ + minlng);
		//cout << "lng_differ to the western side " << lng_differ << endl;
		grid_temp = grid_id - 1;
		value = 1 - 2*lng_differ/differ;
		if(grid_temp > 0 & value > 0)
			GridWeight[grid_temp] = max(value, GridWeight[grid_temp]);
		//cout << grid_temp << " " << value << endl;

		//eastern side
		lng_differ = (lng_id*differ + minlng) - lng;
		//cout << "lng_differ to the eastern side " << lng_differ << endl;
		grid_temp = grid_id + 1;
		value = 1 - 2*lng_differ/differ;
		if(grid_temp < size & value > 0)
			GridWeight[grid_temp] = max(value, GridWeight[grid_temp]);
		//cout << grid_temp << " " << value << endl;


		// to four corner grids
		// the northwest
		differ_temp = edist(lat, lng, nw.lat, nw.lng);
		//grid_temp = (lat_id + 1) * differ + minlat - lat - 1;
		grid_temp = grid_id + lng_num -1;
		value = 1 - differ_temp/cornerdiffer;
		if(grid_temp > 0 & value > 0)
			GridWeight[grid_temp] = max(value, GridWeight[grid_temp]);
		//cout << grid_temp << " " << value << endl;

		//the northeast
		differ_temp = edist(lat, lng, ne.lat, ne.lng);
		//grid_temp = (lat_id + 1) * differ + minlat - lat + 1;
		grid_temp = grid_id + lng_num +1;
		value = 1 - differ_temp/cornerdiffer;
		if(grid_temp < size & value > 0)
			GridWeight[grid_temp] = max(value, GridWeight[grid_temp]);
		//cout << grid_temp << " " << value << endl;

		// the southeast
		differ_temp = edist(lat, lng, se.lat, se.lng);
		//grid_temp = lat - (lat_id * differ + minlat) + 1;
		grid_temp = grid_id - lng_num + 1;
		value = 1 - differ_temp/cornerdiffer;
		if(grid_temp <size & value > 0)
			GridWeight[grid_temp] = max(value, GridWeight[grid_temp]);
		//cout << grid_temp << " " << value << endl;

		// the southwest
		differ_temp = edist(lat, lng, sw.lat, sw.lng);
		//grid_temp = lat - (lat_id * differ + minlat) - 1;
		grid_temp = grid_id - lng_num - 1;
		value = 1 - differ_temp/cornerdiffer;
		if(grid_temp > 0  & value > 0)
			GridWeight[grid_temp] = max(value, GridWeight[grid_temp]);*/
		//cout << grid_temp << " " << value << endl;
		//cout << GridWeight[1] << endl;
	}
	fclose(fp);
	//cout << GridWeight[1] << endl;

	fp = fopen("matrix_sub_gm.txt", "a");
	for(int i = 0; i < size; i++)
	{
		if(GridWeight[i] != 0)
			fprintf(fp, "%d %d %lf\n", trajid, i, GridWeight[i]);
	}


	//cout << lat_num << " " << lng_num << endl;
	


	return 0;
}