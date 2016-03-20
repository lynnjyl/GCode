#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

int main(int argc, char * argv[])
{
	/**************************************************/
	/*get all the index of the cant trajecotry: idlist*/
	int id = atoi(argv[1]);
	string cfile = "../gm/cosine/result/" + to_string(id) +"_cosine_sort";
	vector <int> idlist;
	FILE *fp = fopen(cfile.c_str(), "r");

	int index, temp;
	double val;

	fscanf(fp, "%d %lf\n", &index, &val);
	while(val >= 0.9)
	{
		idlist.push_back(index);
		fscanf(fp, "%d %lf\n", &index, &val);
	}
	fclose(fp);
	/*************************************************/
	//cout << "stage one finished" << endl;


	string lfile;
	int trajid = cfile[0];
	double lval[58182];
	double sum(0), avg(0);
	double max(0), min(10000000);


	/*************************************************/
	/*read the lcss file*/
	lfile = "../lcss/result/lcss_" + to_string(id) + "_sort";
	fp = fopen(lfile.c_str(), "r");


	while(fscanf(fp, "%d %d %lf\n", &index, &temp, &val) != EOF)
	{
		lval[index] = val;
	}
	/*************************************************/


	for(int i = 0; i < idlist.size(); i++)
	{
		sum += lval[idlist[i]];
		if(lval[idlist[i]] > max)
			max = lval[idlist[i]];
		else
			if(lval[idlist[i]] < min)
				min = lval[idlist[i]];
	}
	avg = sum/idlist.size();
	cout << id << " " << avg << endl;
	//cout << "average lcss is " << avg << endl;
	//cout << "min lcss is " << min << endl;
	//cout << "max lcss is " << max << endl;

	return 0;
}