#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct element
{
	int Gid;
	double val;
};

double cosine(vector <element> v1, vector <element> v2)
{
	double cos;
	double product = 0;
	double len1, len2;
	len1 = len2 = 0;

	int index1, index2;
	index1 = index2 = 0;
	
	//vector <element>::iterator it1 = v1.begin();
	//vector <element>::iterator it2 = v2.begin();


	while(index1 != v1.size() && index2 != v2.size())
	{
		/*cout << "index1 = " << index1 << endl;
		cout << "index2 = " << index2 << endl;
		cout << "v1.Gid = " << v1[index1].Gid << endl;
		cout << "v2.Gid = " << v2[index2].Gid << endl;
		cout << "===============================" << endl;*/
		if(v1[index1].Gid == v2[index2].Gid)
		{
			product += (v1[index1].val)*(v2[index2].val);
			index1++;
			index2++;
		}
		else
		{
			if(v1[index1].Gid > v2[index2].Gid)
				index2++;
			else
				index1++;
		}
		len1 += (v1[index1].val)*(v1[index1].val);
		len2 += (v2[index2].val)*(v2[index2].val);
	}
	//cout << v1.size() << endl;
	//cout << v2.size() << endl;
	cos = product/(len1 * len2);

	return cos;
}

int main()
{

	int trajid, gid, queryid = 12602;
	double value;
	element temp;
	vector < vector <element> > matrix;
	matrix.resize(14940);
	FILE *fp = fopen("../../../matrix.txt", "r");

	while(fscanf(fp, "%d %d %lf\n", &trajid, &gid, &value) != EOF)
	{
		temp.Gid = gid;
		temp.val = value;
		matrix[trajid].push_back(temp);
	}

	double cos = cosine(matrix[1], matrix[2]);
	//cout << cos << endl;


	for(int i = 1; i < 14940; i++)
	{
		cos = cosine(matrix[i], matrix[queryid]);
		cout << i << " " << cos << endl;
	}

	return 0;
}