#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <set>

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
		standardf = "./result_10/lcss_" + to_string(qids[i]) + "_sort";
		noisyf = "./result_" + to_string(n) + "/lcss_" + to_string(qids[i]) + "_sort";
		//cout << standardf << " " << noisyf << endl;

		fp = fopen(standardf.c_str(), "r");
		fscanf(fp, "%d %d %lf\n", &id, &num, &rate);
		while(rate >= k)
		{
			stad.push_back(id);
			fscanf(fp, "%d %d %lf\n", &id, &num, &rate);
			c1++;
		}
		fclose(fp);
		//cout << "read standard" << endl;

		fp = fopen(noisyf.c_str(), "r");
		fscanf(fp, "%d %d %lf\n", &id, &num, &rate);
		while(rate >= k)
		{
			noi.push_back(id);
			fscanf(fp, "%d %d %lf\n", &id, &num, &rate);
			c2++;
		}
		fclose(fp);

		set_union(stad.begin(), stad.begin() + c1, noi.begin(), noi.begin() + c2, inserter(uni, uni.begin()));
		set_intersection(stad.begin(), stad.begin() + c1, noi.begin(), noi.begin() + c2, inserter(inter, inter.begin()));

		j = (double)inter.size()/(double)uni.size();
		cout << j << endl;
		jsum += j;

		stad.erase(stad.begin(),stad.begin() + c1);
		noi.erase(noi.begin(), noi.begin() + c2);
		c1 = c2 = 0;
	}
	cout << "average = " << jsum/qids.size() << endl;





	return 0;
}
