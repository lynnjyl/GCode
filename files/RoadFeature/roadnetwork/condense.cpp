// condense the geos.txt file.

#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include "../include/distance.h"
#include "../include/basic.h"
#define pi 3.14159265358979323846


double GetAngle(double lat1, double lng1, double lat2, double lng2)
{
	double angle;
	double dist1, dist2;
	double tangent;
	
	dist1 = distance(lat1, lng1, lat1, lng2);
	dist2 = distance(lat1, lng2, lat2, lng2);
	tangent = dist2/dist1;
	angle = atan(tangent)*180/pi;
	
	return angle;
}

void Condese(string str)
{
	vector <GPSPoint> points;
	GPSPoint pTemp;
	int eid;
	int p1, p2, p3 = 1;
	int size;

	p1 = str.find('\t', 0);
	eid = atoi(str.substr(0, p1++).c_str());
	
	while(p3 > 0)
	{
		p2 = str.find('\t', p1);    //cout << "p2: " << p2 << endl;
        	p3 = str.find('\t', p2+1);  //cout << "p3: " << p3 << endl;
        
        	pTemp.lat = atof(str.substr(p1, p2-p1).c_str());
        	pTemp.lng = atof(str.substr(p2, p3-p2).c_str());
        	p2++;
		p1 = p3+1;

		points.push_back(pTemp);
	}
	size = points.size();
	
}

int main(int argv, char * argc[])
{
	ifstream ifs("geo.txt");
	string str;

	for(int i = 0; i < 433391; i++)
	{
		getline(ifs, str, 'n');
		Condense(str);
	}		

}
