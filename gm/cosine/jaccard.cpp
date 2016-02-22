#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	FILE *fp1, *fp2, *fp3;
	fp1 =fopen(argv[1], "r");
	fp2 = fopen(argv[2], "r");
	int num = atoi(argv[3]);
	vector <int>::iterator it;
	int id, i,temp;
	double val;
	vector <int> v1 ,v2;
	set <int> uni, inter;
	char name[20];
	//string *p;

	vector <string>::iterator iter;
	vector <string> filename;
	filename.push_back("0");

	fp3 = fopen("../index_sub_gm_121.txt", "r");
	while(fscanf(fp3, "%d %s\n", &id, name) != EOF)
	{
		filename.push_back(string(name));
	}


	for(i = 0; i < num; i++)
	{
		//get the cosine/product result.
		fscanf(fp1, "%d %lf\n", &id, &val);
		v1.push_back(id);
		uni.insert(id);
		
		// get the lcss result.
		fscanf(fp2, "%d %d %lf\n", &id, &temp, &val);
		//iter = search_n(filename.begin(), filename.end(), 1, name);
		//cout << name << " " << iter-filename.begin() << endl;
		//ggid = iter-filename.begin();

		v2.push_back(id);
		uni.insert(id);
	}

	for(i = 0; i < num; i++)
	{
		it = find(v1.begin(), v1.end(), v2[i]);
		if(it != v1.end())
			inter.insert(v2[i]);
	}

	cout << uni.size() << endl;
	cout << inter.size() << endl;

	double rate = (double)inter.size()/uni.size();
	cout << rate << endl;




	return 0;
}