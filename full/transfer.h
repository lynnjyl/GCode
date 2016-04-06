#pragma once
#include <random>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include <set>

using namespace std;
// six circle of Beijing
double minlat = 39.688;
double minlng = 116.093;
double maxlat = 40.178;
double maxlng = 116.708;
double differ = 0.0005;
int lat_num = (maxlat - minlat)/differ + 1;
int lng_num = (maxlng - minlng)/differ + 1;
int size = int(lat_num * lng_num) + 1;
double anglediff;
#define pi 3.14159265358979323846

struct element
{
    int gid;
    double val;
    vector <double> angles;
};
struct GPSpoint
{
	double lat;
	double lng;
};
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

vector <element> transfer(string filename)
{
	FILE * fp = fopen(filename.c_str(), "r");
	GPSpoint nw, ne, sw, se;
	double *GridWeight = new double[size];
	fill_n(GridWeight, size, 0);
	double lat, lng, lat_differ, lng_differ, differ_temp, cornerdiffer;
	vector <element> vec;
	char time[20];
	int lat_id, lng_id, grid_id;
	int i;
	double dist, value[9], sum;
	GPSpoint centers[9], temp_point;			
	int centersid[9];
	vector <GPSpoint> grid_point;
	int old_grid = 0, now_grid = 0;
	vector < vector <double> > grid_angle;
	grid_angle.resize(size);
	//GridAngle angle;
	double angle;

	while(fscanf(fp, "%lf %lf %s\n", &lat, &lng, time) != EOF)
	{
		sum = 0;
		lat_id = floor((lat - minlat)/differ);
		lng_id = ceil((lng - minlng)/differ);
		grid_id = lat_id*lng_num + lng_id;		//Id of the grid which the GPS point is in.
 		//cout << lat << " " << lng << " " << grid_id << endl;
 		
		centers[4].lat =  minlat + differ * (lat_id - 1) + differ/2;
		centers[4].lng = minlng + differ * (lng_id -1) + differ/2;
		centersid[4] = grid_id;
		
		/*angle part*/
		if(now_grid == 0)
			now_grid = grid_id;
		temp_point.lat = lat;
		temp_point.lng = lng;

		if(now_grid == grid_id)
			grid_point.push_back(temp_point);
		else
		{
			if(grid_point.size() != 0)
			{
				if(grid_point.size() == 1)
					angle = GetAngle(grid_point[0].lat, grid_point[0].lng, lat, lng);
				else
					angle = GetAngle(grid_point[0].lat, grid_point[0].lng, grid_point[grid_point.size()-1].lat, grid_point[grid_point.size()-1].lng);
			
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
				GridWeight[centersid[i]] = max(value[i], GridWeight[centersid[i]]);
		}

	}

	if(grid_point.size() != 1)
		angle = GetAngle(grid_point[0].lat, grid_point[0].lng, grid_point[grid_point.size()-1].lat, grid_point[grid_point.size()-1].lng);
	else
		angle = grid_angle[old_grid][grid_angle[old_grid].size()-1];

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

	element temp;
	for(int i = 0; i < size; i++)
	{
		if(GridWeight[i] != 0)
		{
			temp.gid = i;
			temp.val = GridWeight[i];
			if(grid_angle[i].size() != 0)
				temp.angles = grid_angle[i];
			
			vec.push_back(temp);
		}
		
		
	}
	cout << vec.size() << endl;
	return vec;
}