#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
	FILE *fp1, *fp2;
	fp1 =fopen(argv[1], "r");
	fp2 = fopen(argv[2], "r");
	int num = atoi(argv[3]);
	vector <int>::iterator it;
	int id, i;
	double val;
	vector <int> v1 ,v2;
	set <int> uni, inter;

	for(i = 0; i < num; i++)
	{
		fscanf(fp1, "%d %lf\n", &id, &val);
		v1.push_back(id);
		uni.insert(id);
		fscanf(fp2, "%d %lf\n", &id, &val);
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




	return 0;
}