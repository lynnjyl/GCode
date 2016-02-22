/*
	get the innerproduct  and cosine value of the query vector and all the other vectors in the matrix.

	input:

	
	argv[1]: queryid;
*/



#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <string.h>

using namespace std;

struct element
{
	int Gid;
	double val;
};

double cosine(vector <element> v1, vector <element> v2, int mode)
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
			index1++;
			index2++;

		}
		else
		{
			if(v1[index1].Gid > v2[index2].Gid)
			{
				index2++;
			}
			else
			{
				index1++;
			}
		}
	}

	for(index1 = 0; index1 < v1.size(); index1++)
		len1 += (v1[index1].val)*(v1[index1].val);
	for(index2 = 0; index2 < v2.size(); index2++)
		len2 += (v2[index2].val)*(v2[index2].val);

	if(mode == 0)
		cos = product/(sqrt(len1)*sqrt(len2));
	else
		cos = product;
	return cos;
}

int main(int argc, char * argv[])
{

	int trajid, gid;
	double value;
	element temp;
	vector < vector <element> > matrix;
	matrix.resize(131247);
	FILE *fp = fopen("../matrix_130.txt", "r");
	//int mode = atoi(argv[1]);
	int queryid = atoi(argv[1]);

	while(fscanf(fp, "%d %d %lf\n", &trajid, &gid, &value) != EOF)
	{
		temp.Gid = gid;
		temp.val = value;
		matrix[trajid].push_back(temp);
	}

	fclose(fp);
	
	double cos, prod;
	string output1, output2;

	output1 = "./result/"+ to_string(queryid) + "_cosine";
	output2 = "./result/" + to_string(queryid) + "_product";
	FILE *fp2 = fopen(output1.c_str(), "w");
	FILE *fp3 = fopen(output2.c_str(), "w");
	for(int i = 1; i < 131247; i++)
	{
		cos = cosine(matrix[i], matrix[queryid], 0);
		prod = cosine(matrix[i], matrix[queryid], 1);
		fprintf(fp2, "%d %lf\n", i, cos);
		fprintf(fp3, "%d %lf\n", i, prod);
	}
	fclose(fp2);
	fclose(fp3);

	return 0;
}
