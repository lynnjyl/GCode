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
	int num1 = atoi(argv[3]);
	int num2 = atoi(argv[4]);
	//vector <int>::iterator it;
	int id, i, temp;
	double val;
	//vector <int> v1 ,v2, uni, inter;
	//set <int> uni, inter;
	set <int> s1, s2, uni, inter, differ1, differ2;
	char name[20];
	//string *p;
	//uni.resize(num1+num2);
	//inter.resize(num1+num2);


	//cout << "cosine" << endl;
	for(i = 0; i < num1; i++)
	{
		fscanf(fp1, "%d %lf\n", &id, &val);
		//cout << id << endl;
		s1.insert(id);
		//uni.insert(id);
	}
		//cout << "lcss" << endl; 

	for(i = 0; i < num2; i++)
	{
		fscanf(fp2, "%d %d %lf\n", &id, &temp, &val);
		s2.insert(id);
		//cout << id << endl;
		//uni.insert(id);
	}

	set_union(s1.begin(), s1.end(), s2.begin(), s2.end(),inserter(uni, uni.begin()));
	//set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(),inserter(differ, differ.begin()));
	set_intersection(s1.begin(),s1.end(),s2.begin(), s2.end(),inserter(inter,inter.begin()));


	cout << "*************Top " << num1 << "**************" << endl;
	cout << "union size        = " << uni.size() << endl;
	cout << "intersection size = " << inter.size() << endl;
	cout << "*******************************" << endl;

	//cout << inter.size() << endl;

	cout << "element appear in set1 but not in set2:" << endl;
	set_difference(s1.begin(), s1.end(), inter.begin(),inter.end(),inserter(differ1,differ1.begin()));
	for(auto k:differ1) cout << k << " ";
		cout << endl;

	cout << endl;
	cout << "element appear in set2 but not in set1:" << endl;
	set_difference(s2.begin(), s2.end(), inter.begin(),inter.end(),inserter(differ2,differ2.begin()));
	for(auto k:differ2) cout << k << " ";
		cout << endl;

/*
	cout << "********************************" << endl;
	for (auto k:inter) cout << k << " ";
		cout << endl;
*/




/*
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.begin());
	cout << "ok" << endl;
	it = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), uni.begin());
	uni.resize(it - uni.begin());
	cout << "union is ok" << endl;
	it = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), inter.begin());
	inter.resize(it - inter.begin());

	cout << "******union******" << endl;
	for (i = 0; i < uni.size(); i++)
		cout << uni[i] << endl;
*/

/*
	for(i = 0; i < num1; i++)
	{
		it = find(v2.begin(), v2.end(), v1[i]);
		if(it != v2.end())
			inter.insert(v1[i]);
		//else
		//	cout << v1[i] << endl;
	}
*/
/*
	for (auto k : differ) cout << k << " ";
		cout << endl;
	cout << uni.size() << endl;
    cout << differ.size() << endl;
	cout << num1+num2-uni.size() << endl;

	double rate = (double)(num1+num2)/uni.size() - 1;
	cout << rate << endl;
*/



	return 0;
}
