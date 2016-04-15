#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])
{
	int n = atoi(argv[1]);
	double k = atof(argv[2]);


	vector <int> qids, stad, noi;
	int id, num;
	double rate;
	set <int> uni, inter;
	FILE *fp = fopen("t.txt", "r");

	while(fscanf(fp, "%d\n", &id) != EOF)
		qids.push_back(id);
	fclose(fp);

	string standardf, noisyf;
	int c1(0), c2(0);
	double j, jsum(0);

	//cout << qids.size() << endl;
	for(int i = 0; i < qids.size(); i++)
	{
		cout << qids[i] << endl;
		standardf = "./result_1/" + to_string(qids[i]) + "_cosine_sort";
		noisyf = "./result_" + to_string(n) + "/" + to_string(qids[i]) + "_cosine_sort";
		//cout << standardf << " " << noisyf << endl;

		fp = fopen(standardf.c_str(), "r");
		fscanf(fp, "%d %lf\n", &id, &rate);
		while(rate >= k)
		{
			stad.push_back(id);
		//	cout << id << endl;
			fscanf(fp, "%d %lf\n", &id, &rate);
			c1++;
		}
		fclose(fp);
		//cout << "read standard" << endl;

		fp = fopen(noisyf.c_str(), "r");
		fscanf(fp, "%d %lf\n", &id, &rate);
		while(rate >= k)
		{
			noi.push_back(id);
		//	cout << id << endl;
			fscanf(fp, "%d %lf\n", &id,&rate);
			c2++;
		}
		fclose(fp);

		sort(stad.begin(),stad.end());
		sort(noi.begin(),noi.end());
		set_union(stad.begin(), stad.begin() + c1, noi.begin(), noi.begin() + c2, inserter(uni, uni.begin()));
		set_intersection(stad.begin(), stad.begin() + c1, noi.begin(), noi.begin() + c2, inserter(inter, inter.begin()));
	//	cout << stad.size() << " " << noi.size() << endl;
		j = (double)inter.size()/(double)uni.size();
		//cout << inter.size() << " " << uni.size() << endl;
		cout << j << endl;
		jsum += j;

		stad.erase(stad.begin(),stad.begin() + c1);
		noi.erase(noi.begin(), noi.begin() + c2);
		inter.erase(inter.begin(),inter.end());
		uni.erase(uni.begin(),uni.end());
		c1 = c2 = 0;
	}
	cout << "average = " << jsum/qids.size() << endl;





	return 0;
}
