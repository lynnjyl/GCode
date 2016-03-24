#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main(int argc, char *argv[])
{
	double lcssthres = atof(argv[1]);
	double costhres = atof(argv[2]);
	int trajid = atoi(argv[3]);


	string lcssname = "../lcss/result/lcss_" + to_string(trajid) + "_sort";
	string cosname = "../gm/cosine/result/" + to_string(trajid) + "_cosine_sort";

	FILE *lfile, *cfile;

	lfile = fopen(lcssname.c_str(), "r");
	cfile = fopen(cosname.c_str(), "r");

	int id, num;
	double rate;
	int count_lcss(0), count_cos(0);
	vector <int> lcss, cosine;

	fscanf(lfile, "%d %d %lf\n", &id, &num, &rate);
	while(rate >= lcssthres)
	{
		lcss.push_back(id);
		fscanf(lfile, "%d %d %lf\n", &id, &num, &rate);
		count_lcss++;
	}

	fscanf(cfile, "%d %lf\n", &id, &rate);
	while(rate >= costhres)
	{
		cosine.push_back(id);
		fscanf(cfile, "%d %lf\n", &id, &rate);
		count_cos++;
	}
	fclose(lfile);
	fclose(cfile);

	sort(lcss.begin(), lcss.end());
	sort(cosine.begin(), cosine.end());

	set <int> inter;

	set_intersection(lcss.begin(), lcss.begin()+count_lcss, cosine.begin(),cosine.begin()+count_cos,inserter(inter,inter.begin()));

	double recall, presicion;

	recall = (double)inter.size()/lcss.size();
	presicion = (double)inter.size()/cosine.size();

	//cout << inter.size() << " " << lcss.size() << " " << cosine.size() << endl;

	cout << trajid << " " << recall << " " << presicion << endl;




	



	return 0;
}