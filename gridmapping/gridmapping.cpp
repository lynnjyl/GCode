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


int main(int argc, char * argv[])
{
	GPSpoint nw, ne, sw, se;
	double *GridWeight = new double[size];
	fill_n(GridWeight, size, 0);
	double lat, lng, lat_differ, lng_differ, differ_temp, cornerdiffer;
	char time[20];
	int lat_id, lng_id, grid_id;
	int grid_temp;
	double value;
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
		grid_id = lat_id*lng_num + lng_id;
		GridWeight[grid_id] = 1;
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
			GridWeight[grid_temp] = max(value, GridWeight[grid_temp]);
		//cout << grid_temp << " " << value << endl;
		//cout << GridWeight[1] << endl;
	}
	fclose(fp);
	//cout << GridWeight[1] << endl;

	fp = fopen("matrix_sub.txt", "a");
	for(int i = 0; i < size; i++)
	{
		if(GridWeight[i] != 0)
			fprintf(fp, "%d %d %lf\n", trajid, i, GridWeight[i]);
	}


	//cout << lat_num << " " << lng_num << endl;
	


	return 0;
}