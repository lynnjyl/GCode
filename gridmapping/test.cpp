#include <iostream>
#include <fstream>
#include <string>

using namespace std;

double minlat = 39.688403;
double minlng = 116.091945;
double maxlat = 40.179632;
double maxlng = 116.714733;

struct GPSpoint
{
	double lat;
	double lng;
};
// get all trajectories file names
void GetAllFilenames(/*vector <int> &fileids, */string *filenames)
{
	FILE *fp = fopen("../dtw/index.txt", "r");
	char name[30];
	int id;

	//cout << "here" << endl;
	while(fscanf(fp, "%d %s\n", &id, name) != EOF)
	{	
			//fileids.push_back(id);
			//cout << name << endl;
			filenames[id] = string(name);
	}
	fclose(fp);
	return;
}

bool inside(GPSpoint p)
{
	if (p.lat < maxlat && p.lat > minlat && p.lng > minlng && p.lng < maxlng)
		return true;
	else
		return false;
}

int main(int argc, char * argv[])
{
	string filenames[18671];
	string filename;
	GetAllFilenames(filenames);
	FILE *fp;
	int count, num;
	//vector <GPSpoint> traj; 
	double lat, lng;
	double maxlat, maxlng, minlat, minlng;
	maxlat = maxlng = 0;
	minlat = minlng = 200;
	char time[20];
	bool flag;
	GPSpoint p;

	for(int i = 1; i < 18671; i++)
	{
		flag = true;
		count = num = 0;
		filename = "../result/" + filenames[i];
		//cout << filename << endl;
		fp = fopen(filename.c_str(), "r");
		if(fp != NULL)
		{
			
			while(fscanf(fp, "%lf %lf %s\n", &lat, &lng, time) != EOF)
			{
			/*	p.lat = lat;
				p.lng = lng;
				//cout << lat << " " << lng << endl;
				flag = inside(p);
				if(!flag)
					num++;
				count++;*/

				if(lat > maxlat)
					maxlat = lat;
				else
					if(lat < minlat)
						minlat = lat;

				if(lng > maxlng)
					maxlng = lng;
				else
					if(lng < minlng)
						minlng = lng;
			}
			fclose(fp);
			/*float rate = (float)num / float(count);
			if(num > 0 && (rate < 0.1))
				cout << "mv " << filenames[i]  << " ../out/" << filenames[i]<< endl;*/
		}
		/*else
			cout << "file not exits" << endl;*/
	}

	cout << "max: " << maxlat << " " << maxlng << endl;
	cout << "min: " << minlat << " " << minlng << endl;
	return 0;
}