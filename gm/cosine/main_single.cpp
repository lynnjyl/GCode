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
	vector <double> angles;
};
double anglediff;


bool GetDirection(element ele1, element ele2)
{
	double differ;
	for(int i = 0; i < ele1.angles.size(); i++)
	{
		for(int j = 0; j < ele2.angles.size(); j++)
		{
			differ = fabs(ele1.angles[i]-ele2.angles[j]);
			if(differ > 180)
				differ = 360-differ;
			if(differ < anglediff)
				return true;
		}
	}
	return false;
}
double cosine(vector <element> v1, vector <element> v2, int mode)
{
	double cos;
	double product = 0;
	double len1, len2;
	len1 = len2 = 0;

	int index1, index2;
	index1 = index2 = 0;
	bool same = false;
	
	//vector <element>::iterator it1 = v1.begin();
	//vector <element>::iterator it2 = v2.begin();


	while(index1 != v1.size() && index2 != v2.size())
	{
		if(v1[index1].Gid == v2[index2].Gid)
		{
			same = GetDirection(v1[index1], v2[index2]);
			if (same)
			{
				product += (v1[index1].val)*(v2[index2].val);
				len1 += (v1[index1].val)*(v1[index1].val);
				len2 += (v2[index2].val)*(v2[index2].val);
			}
			
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
	/*
	for(index1 = 0; index1 < v1.size(); index1++)
		len1 += (v1[index1].val)*(v1[index1].val);
	for(index2 = 0; index2 < v2.size(); index2++)
		len2 += (v2[index2].val)*(v2[index2].val);
*/
	cout << sqrt(len1) << endl;
	cout << sqrt(len2) << endl;
	if(mode == 0)
	{
		if(len1 != 0 && len2 != 0)
			cos = product/(sqrt(len1)*sqrt(len2));
		else
			cos = 0;
	}
	else
		cos = product;
	return cos;
}

int main(int argc, char * argv[])
{

	int trajid, gid, c;
	double value, an;
	element temp;
	vector < vector <element> > matrix;
	matrix.resize(58182);
	FILE *fp = fopen(argv[1], "r");
	//int mode = atoi(argv[1]);
	int queryid = atoi(argv[2]);
	int cantid = atoi(argv[3]);
	anglediff = atof(argv[4]);

	while(fscanf(fp, "%d %d %lf", &trajid, &gid, &value) != EOF)
	{
		temp.Gid = gid;
		temp.val = value;
		//cout << trajid << " " << gid << " " << endl;
			
		c = getc(fp);
		while(c != 10)
		{
			fscanf(fp, "%lf", &an);
		//	m[trajid][i].angles.push_back(an);
			temp.angles.push_back(an);
			c = getc(fp);
		//	cout << " " << an;
		}
		temp.angles.resize(temp.angles.size());
		//cout << endl;
		matrix[trajid].push_back(temp);
		temp.angles.erase(temp.angles.begin(), temp.angles.end());
	}
	cout << "finish reading" << endl;
	fclose(fp);
	
	double cos, prod;
	string output1, output2;

	/*output1 = "./result/"+ to_string(queryid) + "_cosine";
	//output2 = "./result/" + to_string(queryid) + "_product";
	FILE *fp2 = fopen(output1.c_str(), "w");
	//FILE *fp3 = fopen(output2.c_str(), "w");
	for(int i = 1; i < 58182; i++)
	{
		cos = cosine(matrix[i], matrix[queryid], 0);	// get cosine
		//prod = cosine(matrix[i], matrix[queryid], 1);	// get product
		fprintf(fp2, "%d %lf\n", i, cos);
		//fprintf(fp3, "%d %lf\n", i, prod);
	}
	fclose(fp2);
	//fclose(fp3);*/
	cos = cosine(matrix[queryid], matrix[cantid], 0);
	prod = cosine(matrix[queryid], matrix[cantid], 1);
	cout << prod << endl;
	cout << cos << endl;

	return 0;
}
