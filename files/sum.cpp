#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


void GetAllFilenames(/*vector <int> &fileids, */string *filenames)
{
	FILE *fp = fopen("./dtw/index.txt", "r");
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

int GetSect(string t)
{
	int p1, hour;
	p1 = t.find_first_of(':', 0);
    hour = atoi(t.substr(0, p1++).c_str());


	return hour;
}

int main(int argc, char * argv[])
{
	int start = atoi(argv[1]);
	int num = atoi(argv[2]);
	string *filenames = new string [18671];
	string name;
	FILE *fp;
	double lat, lng;
	char time[20];
	string t;
	int timesec[24];
	int sec;
	int i(0);

	memset(timesec, 0, 24*sizeof(int));
	GetAllFilenames(filenames);
	
	cout << "finish geting names" << endl;
	for (i = start; i < num; i++)
	{
		name = "./result/" + filenames[i];
		//cout << i << endl;
		//cout << name << endl;
		fp = fopen(name.c_str(), "r");
		while(fscanf(fp, "%lf %lf %s\n", &lat, &lng, time) != EOF)
		{
			//cout << time << endl;
			t = string(time);
			sec = GetSect(t);
			timesec[sec]++;
		}
	}

	for(i = 0; i < 24; i++)
		cout << i << " " << timesec[i] << endl;

	return 0;
}