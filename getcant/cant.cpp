#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main ()
{
	FILE *fp = fopen("nolist2.txt", "r");
	FILE *fp2 = fopen("../gm/cosine/record_0.5.txt", "r");

	vector <int> list;
	vector <int> no;

	int a, b;
	//int count1(0), count2(0);
	fscanf(fp2, "%d %d\n", &a, &b);
	while(b >= 350)
	{
		list.push_back(a);
		fscanf(fp2, "%d %d\n", &a, &b);
	}

	fclose(fp2);

	while(fscanf(fp, "%d\n", &a) != EOF)
	{	
		no.push_back(a);
	}

	//cout << "read finished" << endl;
	sort(list.begin(), list.begin()+list.size());
	sort(no.begin(), no.begin() + no.size());

	vector <int> inter;
	vector <int> cant;
	//cout << "sorted" << endl;
	set_intersection(list.begin(),  list.begin()+list.size(), no.begin(), no.begin() + no.size(), inserter(inter, inter.begin()));
	set_difference(list.begin(),  list.begin()+list.size(), inter.begin(), inter.begin() + inter.size(), inserter(cant, cant.begin()));

	//cout << "list size = " << list.size() << endl;
	//cout << "inter size = " << inter.size() << endl;
	//cout << "cant size = " << cant.size() << endl;


	for(auto k:cant)
		cout << k << endl;





	return 0;
}