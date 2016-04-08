#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main(int argc, char *argv[])
{
	//double lcssthres = atof(argv[1]);
	double costhres = atof(argv[1]);
	int matrixid = atoi(argv[2]);
	//int trajid = atoi(argv[2]);
	//int trajid;
	int id, num;
	double rate;
	int count_lsh(0), count_cos(0);
	vector <int> lsh, cosine, trajid;
	FILE *lfile, *cfile, *query;
	string cosname;
	string lshname;
	set <int> inter;
	double recall, presicion;
	double recallsum(0), filteredsum(0);
	double filtered;

	//cout << "here" << endl;

	query = fopen("query.txt", "r");
	while(fscanf(query, "%d %d\n", &id, &num) != EOF)
	{
		trajid.push_back(id);
	}
	fclose(query);

	for(int i = 0; i < trajid.size(); i++)
	{


		cosname = "../gm/cosine/result_" + to_string(matrixid) + "/" + to_string(trajid[i]) + "_cosine_sort";
		lshname = "./result/cant_" + to_string(trajid[i]) + ".txt";
		lfile = fopen(lshname.c_str(), "r");
		cfile = fopen(cosname.c_str(), "r");

	//	cout << lshname << endl;

		//cout << "ok" << endl;
		while(fscanf(lfile, "%d\n", &id) != EOF)
		{
			lsh.push_back(id);
			 //cout << id << endl;
			//fscanf(lfile, "%d %d %lf\n", &id, &num, &rate);
			count_lsh++;
		}
		//cout << "ok" << endl;
		fscanf(cfile, "%d %lf\n", &id, &rate);
		while(rate >= costhres)
		{
			cosine.push_back(id);
			fscanf(cfile, "%d %lf\n", &id, &rate);
			count_cos++;
		}
		fclose(lfile);
		fclose(cfile);
	//	cout << "ok" << endl;
		sort(lsh.begin(), lsh.end());
		sort(cosine.begin(), cosine.end());
		//cout << "ok" << endl;
	
		//cout << cosine.size() << endl;
		set_intersection(lsh.begin(), lsh.begin()+count_lsh, cosine.begin(),cosine.begin()+count_cos,inserter(inter,inter.begin()));
		if(inter.size() == 0 )
			recall = 0;
		else
			recall = (double)inter.size()/cosine.size();	//cout<< "recall" << endl;
//		cout << inter.size() << endl;
		//presicion = (double)inter.size()/cosine.size();	cout << "presicion" << endl;
		filtered = 1 - (double)lsh.size()/58181;		//cout << "filtered " << endl;
		//cout << inter.size() << " " << lsh.size() << " " << cosine.size() << endl;
		
//		cout << trajid[i] << " " << recall << " " << filtered << endl;
		lsh.erase(lsh.begin(), lsh.end());
		cosine.erase(cosine.begin(), cosine.end());
		inter.erase(inter.begin(),inter.end());
		recallsum += recall;
		filteredsum += filtered;

		count_cos = 0;
		count_lsh = 0;

	}
	//cout << endl;
//	cout << recallsum << " " << trajid.size() << endl;
//	cout << filteredsum << " " << trajid.size() << endl;
	recall = (double)recallsum/trajid.size();
	filtered = (double)filteredsum/trajid.size();
	cout << recall << " " << filtered << endl;
	return 0;
}
