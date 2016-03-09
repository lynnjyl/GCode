#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#include <string.h>
#include <functional>


using namespace std;

struct GPSpoint
{
	double lat;
	double lng;
};

struct candidate
{
	int id;
	double dist;
};
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


void ReadFile(string filename, vector<GPSpoint> & traj)
{
	cout << "in read file" << endl;
	FILE *fp = fopen(filename.c_str(), "r");
	cout << filename << endl;
	double latitude, longitude;
	char temp[50];
	GPSpoint p;
	while(fscanf(fp, "%lf %lf %s\n", &latitude, &longitude, temp) != EOF)
	{
		p.lat = latitude;
		p.lng = longitude;
		traj.push_back(p);
	}
	fclose(fp);
	return;
}

double Edistance(double lat1, double lng1, double lat2, double lng2)
{
	double a = lat1 - lat2;
	double b = lng1 - lng2;

	return sqrt(a*a + b*b);
}

double DTW(vector<GPSpoint> traj1, vector<GPSpoint> traj2)
{
	//cout << "begin dtw" << endl;
	int size1 = traj1.size();
	int size2 = traj2.size();
	int i, j;
	double mm;

	double **dtw = new double *[size1];
	for(i = 0; i < size1; i++)
		dtw[i] = new double[size2];

	
	for(i = 0; i < size1; i++)
		dtw[i][0] = distance(traj1[i].lat, traj1[i].lng, traj2[0].lat, traj2[0].lng);
	for(i = 0; i < size2; i++)
		dtw[0][i] = distance(traj2[i].lat, traj2[i].lng, traj1[0].lat, traj1[0].lng);

	for(i = 1; i < size1; i++)
	{
		for(j = 1; j < size2; j++)
		{
			mm = min(min(dtw[i-1][j], dtw[i-1][j-1]), dtw[i][j-1]);
			dtw[i][j] = mm + distance(traj1[i].lat, traj1[i].lng, traj2[j].lat, traj2[j].lng);
			//cout << "dtw " << i << " " << j << ": " << dtw[i][j] << endl;
		}
	}

	cout << dtw[size1 -1][size2-1] << endl;

	int k, m, count(0);
	k = size1 - 1;
	m = size2 - 1;

	while(k != 0 && m != 0)
	{
		mm = min(min(dtw[k-1][m], dtw[k-1][m-1]), dtw[k][m-1]);

		if(mm == dtw[k][m-1])
			m=m-1;
		else
		{
			if(mm == dtw[k-1][m-1])
				m = m-1;
			k = k-1;
		}
		count++;
	}

	return dtw[size1-1][size2-1]/count;
}

void GetAllFilenames(/*vector <int> &fileids, */string *filenames)
{
	FILE *fp = fopen("index.txt", "r");
	char name[30];
	int id;

	cout << "here" << endl;
	while(fscanf(fp, "%d %s\n", &id, name) != EOF)
	{	
			//fileids.push_back(id);
			//cout << name << endl;
			filenames[id] = string(name);
	}
	fclose(fp);
	return;
}

bool less_len(const candidate & c1, const candidate &c2)
{
	return c1.dist < c2.dist;
}

void GetAllCandidates(vector <int> &candid)
{
	FILE *fp = fopen("cant.txt", "r");
	int id;
	while(fscanf(fp, "%d\n", &id) != EOF)
		candid.push_back(id+1);			//LSH part id set from 0
	return;
}
int main(int argc, char* argv[])
{
	//FILE *fp = fopen("index.txt", "r");
	vector<GPSpoint> traj1;
	vector<GPSpoint> traj2;
	string queryfile = argv[1];			//	query file name
	string cantfile = argv[2];			//  file to be compared
	int tid = atoi(argv[3]);			// 	Trajectory ID
	//int mode = atoi(argv[4]);
	//vector <string> filenames;
	//string filenames[18671];
	string name;
	//vector <int> fileids;
	double dist/*, max_dist*/;
	int i;

	ReadFile(queryfile, traj1);

	int k = queryfile.find_last_of("/");
	k++;
	name = queryfile.substr(k, queryfile.length()-k);
	cout << name << endl;

	string output = "./DTWResult/candidate_" + name;
	cout << output << endl;


	if(queryfile != cantfile)
	{
		ReadFile(cantfile, traj2);
		cout << "get distance" << endl;
		dist = DTW(traj1, traj2);
		cout << dist << endl;
		
		FILE *fp2 = fopen(output.c_str(), "a");
		fprintf(fp2, "%d %lf\n", tid, dist);
		fclose(fp2);
	}
	
	/*
	else
	{
		cout << "get all filenames" << endl;
		GetAllFilenames(filenames);
		cout << "get all candidates" << endl;
		GetAllCandidates(candid);
		cout << candid.size() << endl;
		cout << "get distance" << endl;
		for(i = 0; i < candid.size(); i++)
		{
			cout << "id : " << candid[i] << endl;
 			cantfile = filenames[candid[i]];
			cout << " name: " << cantfile << endl;
			name = "../result/" + cantfile;
			cout << name << endl;
 			if(queryfile != cantfile)
			{
				cout << "here" << endl;
				ReadFile(name, traj2);
				dist = DTW(traj1, traj2);	cout << dist << endl;
				string output = "cant_" + queryfile;
				FILE *fp2 = fopen(output.c_str(), "a");
				fprintf(fp2, "%d %lf\n", candid[i], dist);
				fclose(fp2);
			}

=======
	string queryfile = argv[1];
	string cantfile = argv[2];
	int tid = atoi(argv[3]);
	//int mode = atoi(argv[4]);
	//vector <string> filenames;
	string filenames[18671];
	string name;
	//vector <int> fileids;
	double dist/*, max_dist*/;
	//int num = atoi(argv[2]);
	//candidate *cant = new candidate[num];
	//candidate cant_temp;
	//int i, j, id, k(0);
	int i;
	char filename[30];
	vector <int> candid;

	ReadFile(queryfile, traj1);

		/*cout << "begin to read" << endl;
	
		//GetAllFilenames(filenames);
		//cout << filenames[0] << endl;
		

		cout << "read finished" << endl;
*/

	if(queryfile != cantfile)
	{
		ReadFile(cantfile, traj2);
		dist = DTW(traj1, traj2);
		string output = "candidate_" + queryfile;
		FILE *fp2 = fopen(output.c_str(), "a");
		fprintf(fp2, "%d %lf\n", tid, dist);
	}
	
	/*
	else
	{
		cout << "get all filenames" << endl;
		GetAllFilenames(filenames);
		cout << "get all candidates" << endl;
		GetAllCandidates(candid);
		cout << candid.size() << endl;
		cout << "get distance" << endl;
		for(i = 0; i < candid.size(); i++)
		{
			cout << "id : " << candid[i] << endl;
 			cantfile = filenames[candid[i]];
			cout << " name: " << cantfile << endl;
			name = "../result/" + cantfile;
			cout << name << endl;
 			if(queryfile != cantfile)
			{
				cout << "here" << endl;
				ReadFile(name, traj2);
				dist = DTW(traj1, traj2);	cout << dist << endl;
				string output = "cant_" + queryfile;
				FILE *fp2 = fopen(output.c_str(), "a");
				fprintf(fp2, "%d %lf\n", candid[i], dist);
				fclose(fp2);
			}

>>>>>>> c60ec2d1794433039f68350acbc812a72adef774
		}
	}
	*/
/*
	for(i = 0; i < 18670; i++)
	{
		//cout << filenames[i] << endl;
		//fscanf(fp, "%d %s\n", &id, filename);
		cout << i << " " <<  filenames[i] << endl;

		if(string(filenames[i]) != queryfile)
		{	
			//cout << "not the same" << endl;
			name = "../result/" + string(filenames[i]);
			
			//cout << name << endl;
			ReadFile(name, traj2);
			cout << "get distance" << endl;
			dist = DTW(traj1, traj2);
			//cout << dist << endl;
			cant_temp.id = i+1;
			cant_temp.dist = dist;
			if(k < num)
			{
				cant[k++] = cant_temp;
				//cout << cant[i].id << " " << cant[i].dist << endl;
			}
			else
			{
				sort(cant, cant+num, less_len);
				max_dist = cant[num-1].dist;

				if(dist < max_dist)
				{
					cant[num-1] = cant_temp;
				}
			}
			
			for(j = 0; j < num; j++)
				cout << cant[j].id << " " << cant[j].dist << endl;
			cout << "**************************" << endl;
			traj2.clear();
		}
		
	}
	//cout << cant[0].id << " " << cant[0].dist << endl;
 
	string output = "candidate_" + queryfile;
	FILE *fp2 = fopen(output.c_str(), "a");

	for(j = 0; j < num; j++)
	{
		fprintf(fp2, "%d %lf\n", cant[j].id, cant[j].dist);
	}
	fclose(fp2);
	fclose(fp);

*/
	//ReadFile(file2, traj2);

	//cout << "read finished" << endl;
	//dist = DTW(traj1, traj2);

	//cout << "Distance: " << dist << endl;




	return 0;
}
