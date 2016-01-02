#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int  main()
{
	FILE *fp = fopen("log_productsort", "r");
	double cosine[131247];
	double cosi;
	int id;
	while(fscanf (fp, "%d %lf\n", &id, &cosi) != EOF)
		cosine[id] = cosi;

	FILE *fp2 = fopen("q", "r");
	vector <int> ids;
	while(fscanf(fp2, "%d %lf\n", &id, &cosi) != EOF)
		ids.push_back(id);

	for(int i = 0; i < ids.size(); i++)
		cout << ids[i] << " " << cosine[ids[i]] << endl;

	return 0;
}