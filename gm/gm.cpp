/*
	use the distance from the GPS point to the grid center to get the weight value.

*/


#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <functional>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

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
double differ = 0.0003;
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


double GetAngle(double lat1, double lng1, double lat2, double lng2)
{
	//cout << lat1 << " " << lng1 << " " << lat2 << " " << lng2 << endl;
	double angle;
	double cosine = (lng1 - lng2)/(sqrt((lng1 - lng2)*(lng1 - lng2) + (lat1 - lat2) * (lat1 - lat2)));
	angle = acos (cosine) * 180 / pi;

	if(lat1 - lat2 < 0)	
		angle = -angle;

	return angle;
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
	int i;
	double dist, value[9], sum;
	GPSpoint centers[9], temp_point;			// the 4 related grids.
	int centersid[9];
	vector <GPSpoint> grid_point;
	int old_grid = 0, now_grid = 0;
	vector < vector <double> > grid_angle;
	grid_angle.resize(size);
	//GridAngle angle;
	double angle;
	
	/* open GPS file and read it */
	int trajid = atoi(argv[1]);
	string filename = argv[2];
	FILE * fp = fopen(filename.c_str(), "r");
	cout << trajid << " " << filename <<  endl;
	
	cornerdiffer = sqrt(differ*differ*2);
	int counter = 1;
	//cout << lng_num << endl;

	/* read file : each GPS point*/
	while(fscanf(fp, "%lf %lf %s\n", &lat, &lng, time) != EOF)
	{
		//fscanf(fp, "%lf %lf %s\n", &lat, &lng, time);
		sum = 0;
		lat_id = floor((lat - minlat)/differ);
		lng_id = ceil((lng - minlng)/differ);
		grid_id = lat_id*lng_num + lng_id;		//Id of the grid which the GPS point is in.
 
		centers[4].lat =  minlat + differ * (lat_id - 1) + differ/2;
		centers[4].lng = minlng + differ * (lng_id -1) + differ/2;
		centersid[4] = grid_id;

//		cout << lat << " " << lng << " " << grid_id << endl;
		
		/*angle part*/
		if(now_grid == 0)
			now_grid = grid_id;
		temp_point.lat = lat;
		temp_point.lng = lng;
		//cout << "grid id = " << grid_id << endl;

		if(now_grid == grid_id)
		{
			//cout << "the same, push back" << endl;
			grid_point.push_back(temp_point);
		}
		else
		{
		//	cout << old_grid << " grid_point size " << grid_point.size() << endl;
			//cout << "not the same" << endl;
			if(grid_point.size() != 0)
			{
				//cout << "not equal to zero " << endl;
				if(grid_point.size() == 1)
					angle = GetAngle(grid_point[0].lat, grid_point[0].lng, lat, lng);
				else
					angle = GetAngle(grid_point[0].lat, grid_point[0].lng, grid_point[grid_point.size()-1].lat, grid_point[grid_point.size()-1].lng);
			
                //cout << angle << endl;
                grid_angle[now_grid].push_back(angle);
                grid_angle[now_grid+1].push_back(angle);
                grid_angle[now_grid-1].push_back(angle);
                grid_angle[now_grid+lng_num].push_back(angle);
                grid_angle[now_grid+lng_num+1].push_back(angle);
                grid_angle[now_grid+lng_num-1].push_back(angle);
                grid_angle[now_grid-lng_num].push_back(angle);
                grid_angle[now_grid-lng_num+1].push_back(angle);
                grid_angle[now_grid-lng_num-1].push_back(angle);
			}
			old_grid = now_grid;
			now_grid = grid_id;
			grid_point.erase(grid_point.begin(), grid_point.end());
			grid_point.push_back(temp_point);
		}
/*
		
*/
		/**************************/

/*
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

		centers[3].lat = centers[1].lat;
		centers[3].lng = centers[2].lng;
		
		if(centersid[2] > centersid[0])
			centersid[3] = centersid[1] + 1;
		else
			centersid[3] = centersid[1] - 1;
		//cout << "centers[3]: " << centersid[3] << " " << centers[3].lat << " " << centers[3].lng << endl;
*/
		centers[1].lng = centers[7].lng = centers[4].lng;
		centers[0].lng = centers[3].lng = centers[6].lng = centers[4].lng - differ;
		centers[2].lng = centers[5].lng = centers[8].lng = centers[4].lng + differ;
		centers[0].lat = centers[1].lat = centers[2].lat = centers[4].lat + differ;
		centers[3].lat = centers[5].lat = centers[4].lat;
		centers[6].lat = centers[7].lat = centers[8].lat = centers[4].lat - differ;
 
		centersid[1] = centersid[4] + lng_num;
		centersid[7] = centersid[4] - lng_num;

		centersid[0] = centersid[1] - 1;
		centersid[2] = centersid[1] + 1;

		centersid[3] = centersid[4] - 1;
		centersid[5] = centersid[4] + 1;

		centersid[6] = centersid[7] - 1;
		centersid[8] = centersid[7] + 1;

		for(i = 0; i < 9; i++)
		{
			dist = distance(lat, lng, centers[i].lat, centers[i].lng);
			value[i] = 1/dist;
			sum += value[i];
		}

		for(i = 0; i < 9; i++)
		{
			value[i] = value[i]/sum;
			if(centersid[i] > 0 && centersid[i] < size)
			{
//				GridWeight[centersid[i]] += value[i];
				GridWeight[centersid[i]] = max(value[i], GridWeight[centersid[i]]);
			}
		}

	}

	if(grid_point.size() != 1)
		angle = GetAngle(grid_point[0].lat, grid_point[0].lng, grid_point[grid_point.size()-1].lat, grid_point[grid_point.size()-1].lng);
	else
		angle = grid_angle[old_grid][grid_angle[old_grid].size()-1];
    //cout << angle << endl;
    grid_angle[now_grid].push_back(angle);
    grid_angle[now_grid+1].push_back(angle);
    grid_angle[now_grid-1].push_back(angle);
    grid_angle[now_grid+lng_num].push_back(angle);
    grid_angle[now_grid+lng_num+1].push_back(angle);
    grid_angle[now_grid+lng_num-1].push_back(angle);
    grid_angle[now_grid-lng_num].push_back(angle);
    grid_angle[now_grid-lng_num+1].push_back(angle);
    grid_angle[now_grid-lng_num-1].push_back(angle);
	
	fclose(fp);

	//cout << "here" << endl;

	//cout << grid_angle[799964].size() << endl;
	fp = fopen("matrix_308.txt", "a");
	FILE *anglefile = fopen("angle_308.txt", "a");
	for(int i = 0; i < size; i++)
	{
		if(GridWeight[i] != 0)
			fprintf(fp, "%d %d %lf\n", trajid, i, GridWeight[i]);
		if(grid_angle[i].size()!=0)
		{
			//cout << i << endl;
			fprintf(anglefile, "%d %d", trajid, i);
			for(int j = 0; j < grid_angle[i].size(); j++)
				fprintf(anglefile, " %lf", grid_angle[i][j]);
			fprintf(anglefile, "\n");
		}
	}

	return 0;
}
