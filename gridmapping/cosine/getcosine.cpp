#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct element
{
	int id;
	double cosi;
};

int  main()
{
	FILE *fp = fopen("log_productsort", "r");
	element cosine[131247];
	double cosi;
	int id;
	int i = 0;
	while(fscanf (fp, "%d %lf\n", &id, &cosi) != EOF)
	{
		cosine[i].cosi = cosi;
		cosine[i++].id = id;
	}

	FILE *fp2 = fopen("q", "r");
	vector <int> ids;
	while(fscanf(fp2, "%d %lf\n", &id, &cosi) != EOF)
		ids.push_back(id);

	for(int i = 0; i < ids.size(); i++)
	{
		for(int j = 0; j < 131247; j++)
		{
			if(ids[i] == cosine[j].id)
				cout << ids[i] << " " << cosine[j].cosi << " " << j << endl;
		}
		//cout << ids[i] << " " << cosine[ids[i]] << endl;
	}
	return 0;
}