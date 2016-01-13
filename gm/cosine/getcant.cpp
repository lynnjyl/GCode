#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	FILE *fp1, *fp2;

	fp1 = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "r");
	double thrs = atof(argv[3]);

	double prod[131247], cosine[131247];
	int id;
	double val;
	vector <int> cant;

	while(fscanf(fp1, "%d %lf\n", &id, &val) != EOF)
		prod[id] = val;
	while(fscanf(fp2, "%d %lf\n", &id, &val) != EOF)
		cosine[id] = val;


	int i = 1;
	while(i < 131247)
	{
		if(cosine[i] > thrs && prod[i] > 0)
		{
			cant.push_back(i);
			cout << i << endl;
		}
		i++;
	}


	return 0;
}