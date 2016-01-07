/*
	get the innerproduct  or cosine value of the query vector and all the other vectors in the matrix.

	input:

	argv[1]: mode. mode = 0: cosine value; else: innerproduct;
	argv[2]: queryid;
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
	FILE *fp = fopen("../../../matrix_sub_gm.txt", "r");
	int mode = atoi(argv[1]);
	int queryid = atoi(argv[2]);

	while(fscanf(fp, "%d %d %lf\n", &trajid, &gid, &value) != EOF)
	{
		temp.Gid = gid;
		temp.val = value;
		matrix[trajid].push_back(temp);
	}

	fclose(fp);
	double cos = cosine(matrix[1], matrix[2], mode);
	//cout << cos << endl;

	string output;
	if(mode == 0)
		output = to_string(queryid) + "_cosine";
	else
		output = to_string(queryid) + "_innerproduct";

	FILE *fp2 = fopen(output.c_str(), "w");

	for(int i = 1; i < 131247; i++)
	{
		cos = cosine(matrix[i], matrix[queryid], mode);
		//cout << i << " " << cos << endl;
		fprintf(fp2, "%d %lf\n", i, cos);
	}

/*	cos = cosine(matrix[2536], matrix[105534]);
	cout << cos <<endl;*/



	return 0;
}