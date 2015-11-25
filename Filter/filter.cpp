#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>

using namespace std;


template <typename T>
string NumberToString ( T Number )
{
	stringstream ss;
	ss << Number;
	return ss.str();
}


bool Right(string str, int start, int end)
{
	bool flag = false;

	int pos1 = str.find_first_of(':', 0);
	pos1 = pos1 - 2;

	string hour = str.substr(pos1, 2);
	//cout << hour << endl;

	int h = stoi(hour);
	//cout << h << endl;

	if(h >= start && h <= end)
		flag = true;

	return flag;
}


int main(int argc, char * argv[])
{
	//FILE *fp;

	ifstream fin(argv[1]);
	int start, end;
	//char lat[20],lng[20], time[100];
	string str;
	vector <string> result;

	//fp = fopen(argv[1], "r");
	start = atoi(argv[2]);
	end = atoi(argv[3]);
	cout << "begin" << endl;

	while(getline(fin, str))
	{
		//cout << str << endl;

		if(Right(str, start, end))
			result.push_back(str);
	}

	fin.close();

	cout << "ok " << endl;
	ofstream fout(argv[4]);

	vector <string>::iterator iter = result.begin();

	while(iter != result.end())
	{
		fout << *iter << endl;
		iter++;
	}

	/*while(fscanf(fp, "\n", time) != EOF)
	{
		cout << time << endl;
	}*/

	return 0;
}