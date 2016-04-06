#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <sys/time.h>
#include <string>
#include <set>
#include "lsh.h"
#include "transfer.h"

using namespace std;




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

	while(index1 != v1.size() && index2 != v2.size())
	{
		if(v1[index1].gid == v2[index2].gid)
		{
			same = GetDirection(v1[index1], v2[index2]);
			if (same)
				product += (v1[index1].val)*(v2[index2].val);
			
			index1++;
			index2++;
		}
		else
		{
			if(v1[index1].gid > v2[index2].gid)
				index2++;
			else
				index1++;
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
double wallclock(void) 
{
	struct timeval tv;
	struct timezone tz;
	double t;
	gettimeofday(&tv, &tz);
	t = (double)tv.tv_sec*1000;
	t += ((double)tv.tv_usec)/1000.0;
	return t;
}

int main(int argc, char * argv[])
{

	int trajid, gid, c;
	double value, an;
	element temp;
	vector < vector <element> > matrix;
	matrix.resize(58182);
	FILE *fp = fopen(argv[1], "r");
	anglediff = atof(argv[2]);			//angle difference in angle comparison

	//begin to read the matrix.
	while(fscanf(fp, "%d %d %lf", &trajid, &gid, &value) != EOF)
	{
		temp.gid = gid;
		temp.val = value;
		
		c = getc(fp);
		while(c != 10)
		{
			fscanf(fp, "%lf", &an);
			temp.angles.push_back(an);
			c = getc(fp);
		}
		temp.angles.resize(temp.angles.size());
		matrix[trajid].push_back(temp);
		temp.angles.erase(temp.angles.begin(), temp.angles.end());
	}
	cout << "finish reading" << endl;
	fclose(fp);

	//create the LSH 
	 rhpLsh rhplsh;
    	Parameter_rhplsh param_rhp;
    	param_rhp.M = 512;                        // hash table size
    	param_rhp.L = 20;                     // number of hash tables
    	param_rhp.D = 1205401;                                 // dimension
    	param_rhp.N = 6;                        // binary code byte
    	rhplsh.reset(param_rhp);

    	for(int i = 1; i < 58182; i++)
        		rhplsh.insert(i, matrix[i]);
        	cout << "create LSH finished" << endl;

        	//read the query trajectory and transfer it to a vector;
        	double t1 = wallclock();
        	trajid = atoi(argv[3]);
        	string filename = "../Data/new/" + to_string(trajid);
        	vector <element> vec = transfer(filename);
        	double t2 = wallclock();
        	cout << "transfer part finished" << endl;

        	double t3 = wallclock();
        	//lsh part
        	int mode = atoi(argv[4]);
        	set <unsigned> candidates;
        	double cos;
        	double querytime;
        	if(mode == 1)
        	{
        		cout << "begin lsh query" <<endl;
        		double t6 = wallclock();
        		candidates = rhplsh.query(vec);
        		double t7 = wallclock();
        		cout << "query finished" << endl;
        		cout << "lsh query time:" << t7-t6 << endl;
        		t3 = wallclock();
        		for(set <unsigned>::iterator it = candidates.begin(); it != candidates.end(); ++it)
        			cos = cosine(matrix[distance(candidates.begin(), it)], vec, 0);
        		double t4 = wallclock();
        		cout << candidates.size() << endl;
        		querytime = t4-t3;

        	}
        	else
        	{	
        		t3 = wallclock();
        		for(int i = 0; i < 58182; i++)
        			cos = cosine(matrix[i], vec, 0);
        		double t5 = wallclock();
        		querytime = t5-t3;
        	}

   	cout << "***********************" << endl;
   	cout << "transfer time : " << t2-t1 << endl;
   	cout << "query time: " << querytime << endl;
   	cout << "***********************" << endl;
	
	
	return 0;
}