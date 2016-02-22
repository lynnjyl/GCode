#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{

	FILE *fprod, *flcss, *file;
	int num;
	double data[131247][2];
	int i, j(0);
	int id, temp;
	double val;
	vector <string> filename;
	vector <int> cantid;
	char name[20];
	vector <string>::iterator iter;

	fprod = fopen(argv[1], "r");
	flcss = fopen(argv[2], "r");
	num = atoi(argv[3]);
	int mode = atoi(argv[4]);
	//char a;


	//cout << "ok" << endl;
	if (mode == 1)
	{
		for(i = 0; i < 131247; i++)
		{
			fscanf(fprod, "%d %lf\n", &id, &val);
	//	cout << id << endl;
	//	cout << "product id : " << id << " " << val << endl;
			data[id][0] = val;
			if(j < num)
			{
	//		cout << id << endl;
				cantid.push_back(id);
				j++;
			}
		//cout << i << endl;
			fscanf(flcss, "%d %d %lf\n", &id, &temp, &val);
			data[id][1] = val;
	//	cout << "lcss id : " << id << " " << val << endl;
	//	cin >> a;
		}
	}
	else
	{
		for(i = 0; i < 131247; i++)
		{
			fscanf(fprod, "%d %lf\n", &id, &val);
	//	cout << id << endl;
	//	cout << "product id : " << id << " " << val << endl;
			data[id][0] = val;
			
		//cout << i << endl;
			fscanf(flcss, "%d %d %lf\n", &id, &temp, &val);
			data[id][1] = val;
			if(j < num)
			{
	//		cout << id << endl;
				cantid.push_back(id);
				j++;
			}
	//	cout << "lcss id : " << id << " " << val << endl;
	//	cin >> a;
		}

	}
	cout << "here" << endl;

	double sum(0), avg;
	for(i = 0; i < num; i++)
	{
		//cout << cantid.begin() << endl;
		cout << i << " : " << cantid[i] << " " << data[cantid[i]][0] << " " << data[cantid[i]][1] << endl;
		sum += data[cantid[i]][1];
	}
	avg = sum/num;
	cout << "average is " << avg << endl;


	return 0;
}
