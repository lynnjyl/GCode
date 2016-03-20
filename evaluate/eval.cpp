#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

/*struct cresult
{
	int id;
	double cval;
}*/

int main(int argc, char *argv[])
{
	int traj = atoi(argv[1]);

	string lcssfile = "../lcss/result/lcss_" + to_string(traj) + "_sort";
	string cosinefile = "../gm/cosine/result/" + to_string(traj) + "_cosine_sort";

	FILE *lfp = fopen(lcssfile.c_str(), "r");
	FILE *cfp = fopen(cosinefile.c_str(), "r");

	int id, num;
	double lval, cval;

	vector <int> lcant;
	//vector <double> lvalue;
	vector <int> ccant;
	//vector <double> cvalue;
	double cvalue[58182];
	double lvalue[58182];
	vector <int>::iterator it;

	// lval = 1;
	
	int count(0);
	while(fscanf(lfp, "%d %d %lf\n", &id, &num, &lval) != EOF)
	{
		lcant.push_back(id);
		lvalue[id] = lval;
		//fscanf(lfp, "%d %d %lf\n", &id, &num, &lval);
		if(lval >= 0.6)
			count++;
	}
	fclose(lfp);

	while(fscanf(cfp, "%d %lf\n", &id, &cval) != EOF)
	{	
		//cout << id << " " << cval << endl;
		ccant.push_back(id);
		cvalue[id] = cval;
		//cout << cval << endl;
	}
	fclose(cfp);

	int i(0), index(0);
	int max(0);
	//cout << count << endl;

	for(i = 0; i < count; i++)
	{
		index = distance(ccant.begin(), find(ccant.begin(), ccant.end(), lcant[i]));
		//cout << "Traj " << lcant[i] << ": LCSS = " << lvalue[lcant[i]] << ", Cosine value = " << cvalue[ccant[index]] << ", in position " << index << endl;
		if(index > max)
			max = index;
	}
	//cout << " ******************* Traj " << traj << " ***********************" << endl;
	//cout <<traj << " " << max << " " << ccant[max] << " " << cvalue[ccant[max]] << endl;
	//cout << ccant.begin() + (max) << endl;


	sort(lcant.begin(), lcant.begin()+count);
	sort(ccant.begin(), ccant.begin()+max);
	set <int> differ1;

	set_difference(ccant.begin(), ccant.begin()+max, lcant.begin(),lcant.begin()+count,inserter(differ1,differ1.begin()));
	//cout << lcant.size() << " " << max << " " << differ1.size() << endl;

	double sum(0), avg(0);
	for(auto k:differ1)
	{
		//cout << k << " " << lvalue[k] << " " << cvalue[k] << endl;
		sum += lvalue[k];
	}
	avg = sum/(differ1.size());
	//cout << differ1.size() << endl;
	cout << traj <<" " <<  avg << endl;


	//sort(lcant)


	return 0;
}