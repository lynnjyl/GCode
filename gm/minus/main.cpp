#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

struct element
{
	int Gid;
	double val;
};

double norm(vector <element> v1, vector <element> v2)
{
	double n = 0;
	//double product = 0;
	//double len1, len2;
	//len1 = len2 = 0;

	int index1, index2;
	index1 = index2 = 0;

	while(index1 != v1.size() && index2 != v2.size())
	{
		/*cout << "index1 = " << index1 << endl;
		cout << "index2 = " << index2 << endl;
		cout << "v1.Gid = " << v1[index1].Gid << endl;
		cout << "v2.Gid = " << v2[index2].Gid << endl;
		cout << "===============================" << endl;*/

		if(v1[index1].Gid == v2[index2].Gid)
		{
			/*product += (v1[index1].val)*(v2[index2].val);
			index1++;
			index2++;*/
			n += (v1[index1].val - v2[index2].val)*(v1[index1].val - v2[index2].val);
			index1++;
			index2++;
		}
		else
		{
			if(v1[index1].Gid > v2[index2].Gid)
			{	
				n += v2[index2].val * v2[index2].val;
				index2++;
			}
			else
			{
				n += v1[index1].val * v1[index1].val;
				index1++;
			}
		}
		//len1 += (v1[index1].val)*(v1[index1].val);
		//len2 += (v2[index2].val)*(v2[index2].val);
	}
	//cout << v1.size() << endl;
	//cout << v2.size() << endl;
	//cos = product/(len1 * len2);
	n = sqrt(n);

	return n;
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
	cout << "read finished" << endl;
	//double cos = cosine(matrix[1], matrix[2]);
	//cout << cos << endl;
	double n;


	for(int i = 1; i < 14940; i++)
	{
		n = norm(matrix[i], matrix[queryid]);
		cout << i << " " << n << endl;
	}


	return 0;
}