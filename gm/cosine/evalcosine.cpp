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
	FILE *cosine, *dtw;
	vector <int> cosid;
	vector <double> cosval;
	vector <int> dtwid;
	vector <double> dtwval;
	vector <int>::iterator it;
	int num = atoi(argv[1]);
	int id;
	double val;
	
	cosine = fopen(argv[2], "r");
	dtw = fopen(argv[3], "r");
	cout << "oik" << endl;
	//int index = 0;
	while(fscanf(cosine, "%d %lf\n", &id, &val) != EOF)
	{
		cosid.push_back(id);
		cosval.push_back(val);
	}
	fclose(cosine);

	while(fscanf(dtw, "%d %lf\n", &id, &val) != EOF)
	{
		dtwid.push_back(id);
		dtwval.push_back(val);
	}
	fclose(dtw);

	int count = 0;
	for(int i = 0; i < num; i++)
	{
		it = search_n(dtwid.begin(), dtwid.end(), 1, cosid[i]);
		cout << i << ": " << cosid[i] << ", Cosine Value = " << cosval[i] << endl;
		cout << "DTW index = " << (it-dtwid.begin()) << ", DTW Value = " << dtwval[it-dtwid.begin()] << endl;
		cout << "*********************************" <<endl;
		if(dtwval[it-dtwid.begin()] < 0.4)
			count++;
	}
	double per = (double)count/(double)num;
	cout << "count = " << count << ", number = " << num << ", per = " << per<< endl;




	return 0;
}