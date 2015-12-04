#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;


// six circle of Beijing
double minlat = 39.688;
double minlng = 116.093;
double maxlat = 40.178;
double maxlng = 116.708;
double differ = 0.0005;

int lat_num = (maxlat - minlat)/differ + 1;
int lng_num = (maxlng - minlng)/differ + 1;

int main(int argc, char * argv[])
{
	int size = int(lat_num * lng_num) + 1;
	double *GridWeight = new double[size];
	double lat, lng, lat_differ, lng_differ;
	char time[20];
	int lat_id, lng_id, grid_id;
	int grid_temp;
	double value;
	string filename = "../result/00020081023025304.plt";
	FILE * fp = fopen(filename.c_str(), "r");
	cout << "file opened" << endl;

	cout << lat_num << " " << lng_num << endl;
	

	/*while(fscanf(fp, "%lf %lf %s\n", &lat, &lng, time) != EOF)
	{*/
		fscanf(fp, "%lf %lf %s\n", &lat, &lng, time);
		lat_id = floor((lat - minlat)/differ);
		lng_id = ceil((lng - minlng)/differ);
		grid_id = lat_id*lng_num + lng_id;
		GridWeight[grid_id] = 1;
		cout << lat_id << " " << lng_id << " " << grid_id << endl;

		//distance to the boundary
		// the northern side
		lat_differ = (lat_id + 1) * differ + minlat - lat;
		cout << "lat_differ to the northern side " << lat_differ << endl;
		grid_temp = grid_id + lng_num;
		value = 1 - lat_differ/differ;
		if(grid_temp < size & value > 0)
			GridWeight[grid_temp] = value;
		cout << grid_temp << " " << value << endl;


		// the southern side
		lat_differ = lat - (lat_id * differ + minlat);
		cout << "lat_differ to the southern side " << lat_differ << endl;
		grid_temp = grid_id - lng_num;
		value = 1 - lat_differ/differ;
		if(grid_temp > 0 & value > 0)
			GridWeight[grid_temp] = value;
		cout << grid_temp << " " << value << endl;


		// the western side
		lng_differ = lng - ((lng_id-1) *differ + minlng);
		cout << "lng_differ to the western side " << lng_differ << endl;
		grid_temp = grid_id - 1;
		value = 1 - lng_differ/differ;
		if(grid_temp > 0 & value > 0)
			GridWeight[grid_temp] = value;
		cout << grid_temp << " " << value << endl;

		//eastern side
		lng_differ = (lng_id*differ + minlng) - lng;
		cout << "lng_differ to the eastern side " << lng_differ << endl;


	//}


	//cout << lat_num << " " << lng_num << endl;
	


	return 0;
}