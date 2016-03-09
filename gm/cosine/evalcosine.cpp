#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
bool mypredicate (int i, int j) {
  return (i==j);
}

int main(int argc, char * argv[])
{
	FILE *cosine, *lcss;
	vector <int> cosid;
	vector <double> cosval;
	vector <int> lcssid;
	vector <double> lcssval;
	vector <int>::iterator it;
	int num = atoi(argv[3]);
	int id, temp;
	double val;
	double sum(0), avg(0);
	
	cosine = fopen(argv[1], "r");
	lcss = fopen(argv[2], "r");
	cout << "ok" << endl;
	//int index = 0;
	while(fscanf(cosine, "%d %lf\n", &id, &val) != EOF)
	{
		cosid.push_back(id);
		cosval.push_back(val);
	}
	fclose(cosine);
	cout << "read cosine finished" <<endl;

	while(fscanf(lcss, "%d %d %lf\n", &id, &temp, &val) != EOF)
	{
		//cout << id << " " << val << endl;
		lcssid.push_back(id);
		lcssval.push_back(val);
	}
	fclose(lcss);
	cout << "read lcss finished" << endl;

	int count = 0;
	for(int i = 0; i < num; i++)
	{
		it = search_n(lcssid.begin(), lcssid.end(), 1, cosid[i]);
		cout << i << ": " << cosid[i] << ", Cosine Value = " << cosval[i] << endl;
		cout << "LCSS index = " << (it-lcssid.begin()) << ", LCSS Value = " << lcssval[it-lcssid.begin()] << endl;
		cout << "*********************************" <<endl;
		sum += lcssval[it-lcssid.begin()];
		if(lcssval[it-lcssid.begin()] < 0.4)
			count++;
	}

	avg = sum/num;
	cout << "average  = " << avg << endl;
	//double per = (double)count/(double)num;
	//cout << "count = " << count << ", number = " << num << ", per = " << per<< endl;




	return 0;
}