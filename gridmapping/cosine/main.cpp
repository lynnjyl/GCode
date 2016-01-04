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
		/*	cout << index1 << " " << index2 << " " << v1[index1].Gid << endl;
			cout << "v1 : " << v1[index1].Gid << " " << v1[index1].val << endl;
			cout << "v2 : " << v2[index2].Gid << " " << v2[index2].val << endl;
			cout << "*************" << endl;*/
			product += (v1[index1].val)*(v2[index2].val);
			//len1 += (v1[index1].val)*(v1[index1].val);
			///len2 += (v2[index2].val)*(v2[index2].val);
			index1++;
			index2++;

		}
		else
		{
			if(v1[index1].Gid > v2[index2].Gid)
			{
				//len2 += (v2[index2].val)*(v2[index2].val);
				index2++;
			}
			else
			{
				//len1 += (v1[index1].val)*(v1[index1].val);
				index1++;
			}
		}
		//len1 += (v1[index1].val)*(v1[index1].val);
		//len2 += (v2[index2].val)*(v2[index2].val);
	}

	for(index1 = 0; index1 < v1.size(); index1++)
		len1 += (v1[index1].val)*(v1[index1].val);
	for(index2 = 0; index2 < v2.size(); index2++)
		len2 += (v2[index2].val)*(v2[index2].val);
	//cout << v1.size() << endl;
	//cout << v2.size() << endl;
	//cout << product << endl;
	//cout << len1 << " " << len2 << endl;
	//cos = product/(len1 * len2);
	//cos = product/(sqrt(len1)*sqrt(len2));
	cos = product;
	return cos;
}

int main()
{

	int trajid, gid, queryid = 31660;
	double value;
	element temp;
	vector < vector <element> > matrix;
	matrix.resize(131247);
	FILE *fp = fopen("../../../matrix_sub.txt", "r");

	while(fscanf(fp, "%d %d %lf\n", &trajid, &gid, &value) != EOF)
	{
		temp.Gid = gid;
		temp.val = value;
		matrix[trajid].push_back(temp);
	}

	double cos = cosine(matrix[1], matrix[2]);
	//cout << cos << endl;


	for(int i = 1; i < 131247; i++)
	{
		cos = cosine(matrix[i], matrix[queryid]);
		cout << i << " " << cos << endl;
	}

/*	cos = cosine(matrix[2536], matrix[105534]);
	cout << cos <<endl;*/
	return 0;
}