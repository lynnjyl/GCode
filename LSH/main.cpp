#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <ctime>
#include <sstream>
#include <limits>
#include <sys/time.h>
#include <functional> 
#include "lsh.h"

using namespace std;

void RandomShuffle(vector <int> &a)
{
	//int a[10];
	mt19937 rng(unsigned(time(0)));
	//cout <<rng() << endl;
	int size = a.size();
    int i(0), r(0), temp(0);
    
    //cout <<rng() << endl;
    //cout <<"ok" << endl;
    for(i = 0; i < size; i++)
    {
        r = rng()%size;
        temp = a[i];
        a[i] = a[r];
        a[r] = temp; 
    }
    return;
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

template <typename T>
string NumberToString ( T Number )
{
	stringstream ss;
	ss << Number;
	return ss.str();
}

int main(int argc, char * argv[])
{
	FILE *fp = fopen("matrix.txt", "r");		// the file stores the original matrix
	int TrajID, GridID, i, j, k, CurrentTraj(1);
	int Dim(488600), NumofTraj(18671);
	int SigSize = atoi(argv[1]); 
	int QueryID = atoi(argv[2]);
	//int mode = atoi(argv[3]);
	int maxid = 0, num = 0;
	vector <int> pi;							//vector for min-hashing
	vector < vector<int> > matrix;
	//unsigned Sigmatrix[NumofTraj][SigSize];
	vector < vector<unsigned> > Sigmatrix;
	int minhash;
	matrix.resize(NumofTraj);
	pi.resize(Dim);
	Sigmatrix.resize(NumofTraj);
	string filename;


	// set pi array
	for(i = 0; i < Dim; i++)
		pi[i] = i;
///////////////////////////////////////////////////////////////////
	//get the trajectory matrix
	while(fscanf(fp, "%d %d\n", &TrajID, &GridID) != EOF)
		matrix[TrajID].push_back(GridID);
	
	//cout << "Read Finished" << endl;
	fclose(fp);

	//get signature matrix
	for(j = 0; j < SigSize; j++)
	{
		double t1 = wallclock();
		RandomShuffle(pi);

		double t2 = wallclock();
		//cout << t2 - t1 << endl;

		for(k = 1; k < NumofTraj; k++)		//from 1
		{
			minhash = Dim;
			Sigmatrix[k].resize(SigSize);
			for(i = 0; i < matrix[k].size(); i++)
			{
				if(minhash > pi[i])
					minhash = pi[i];
				//cout << "minhash: " << minhash << endl;
			}
			Sigmatrix[k][j] = minhash;
		}
	}
	//cout << "Get Sigmatrix" << endl;
//////////////////////////////////////////////////////////////////////////	
	matrix.clear();
	for(j = 0; j < NumofTraj; j++)
		vector <int>().swap(matrix[i]);
//////////////////////////////////////////////////////////////////////////
	set <unsigned> candidates;
	

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>rbslsh part
	rbsLsh mylsh;
	Parameter_rbslsh param;
	param.M = 10000;              // Hash table size
    param.L = 10;                // Number of hash tables
    param.D = SigSize;    		// Dimension of the vector, it can be obtained from the instance of Matrix
    param.C = Dim; //×î´óÖµ       // The Difference between upper and lower bound of each dimension
    param.N = 300;               // Binary code bytes
    mylsh.reset(param);
    //std::cout << "Success in rbslsh" << std::endl;
    //std::cout << "hash table size: " << param.M << std::endl;

    for(i = 1; i < NumofTraj; i++)
    	mylsh.insert(i, Sigmatrix[i]);
    	
	candidates = mylsh.query(Sigmatrix[QueryID]);
	//cout << "Traj " << QueryID << " has " << candidates.size() << " candidates." << endl;
	
	filename = "./RbsLsh/cant_" + NumberToString(QueryID) + ".txt";
	fp = fopen(filename.c_str(), "w");
	for(set <unsigned>::iterator it = candidates.begin(); it != candidates.end(); ++it)
		fprintf(fp, "%d\n", *it);
	candidates.clear();
	fclose(fp);

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>psdlsh part
    /*psdLsh psdlsh;
    Parameter_psdlsh param_psd;
    param_psd.M = 1000;
    param_psd.L = 5;
    param_psd.D = SigSize;
    param_psd.T = GAUSSIAN;
    param_psd.W = 0.5;
    psdlsh.reset(param_psd);
    std::cout << "Success in psdlsh" << std::endl;

    for(i = 1; i < NumofTraj; i++)
    	psdlsh.insert(i, Sigmatrix[i]);
    
  
	candidates = psdlsh.query(Sigmatrix[QueryID]);
	cout << "traj " << QueryID << " has " << candidates.size() << " candidates." << endl;
	
	filename = "./PsdLsh/cant_" + NumberToString(QueryID) + ".txt";
	fp = fopen(filename.c_str(), "w");
	for(set <unsigned>::iterator it = candidates.begin(); it != candidates.end(); ++it)
		fprintf(fp, "%d\n", *it);
	candidates.clear();
	fclose(fp);*/

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>rhplsh part
	/*rhpLsh rhplsh;
	Parameter_rhplsh param_rhp;
	param_rhp.M = 1000;
	param_rhp.L = 5;
	param_rhp.D = SigSize;
	param_rhp.N = 6;
	rhplsh.reset(param_rhp);
	std::cout << "Success in rhplsh" << std::endl;

	for(i = 1; i < NumofTraj; i++)
		rhplsh.insert(i, Sigmatrix[i]);
	//cout << "ok";

	//set <unsigned> candidates;


	candidates = rhplsh.query(Sigmatrix[QueryID]);
	cout << "traj " << QueryID << " has " << candidates.size() << " candidates." << endl;

	filename = "./RhpLsh/cant_" + NumberToString(QueryID) + ".txt";
	fp = fopen(filename.c_str(), "w");
	for(set <unsigned>::iterator it = candidates.begin(); it != candidates.end(); ++it)
		fprintf(fp, "%d\n", *it);
	candidates.clear();
	fclose(fp);*/

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>thlsh part
	/*thLsh thlsh;
	Parameter_thlsh param_th;
	param_th.M = 1000;
	param_th.L = 5;
	param_th.D = SigSize;
	param_th.N = 12;
	param_th.Max = std::numeric_limits<float>::max();
	param_th.Min = - std::numeric_limits<float>::max();
	//cout << "begin to set max and min" << endl;
	for (i = 1; i != NumofTraj; ++i)
    {
        for (j = 0; j != SigSize; ++j)
        {
            if (Sigmatrix[i][j] > param_th.Max)
            {
                param_th.Max = Sigmatrix[i][j];
            }
            if (Sigmatrix[i][j] < param_th.Min)
            {
                param_th.Min = Sigmatrix[i][j];
            }
        }
    }
    //set <unsigned> candidates;
    for(i = 0; i < 1; i++)
    {
    	candidates = psdlsh.query(Sigmatrix[i]);
    	cout << "traj " << i << "has " << candidates.size() << " candidates." << endl;
    	
    	FILE *fp = fopen("cant.txt", "w");
    	for(set <unsigned>::iterator it = candidates.begin(); it != candidates.end(); ++it)
    		fprintf(fp, "%d\n", *it);
    	candidates.clear();
    }
    thlsh.reset(param_th);

    for(i = 1; i < NumofTraj; i++)
		thlsh.insert(i, Sigmatrix[i]);
	std::cout << "Success in thlsh" << std::endl;
	//set <unsigned> candidates;

	candidates = thlsh.query(Sigmatrix[QueryID]);
	cout << "traj " << QueryID << " has " << candidates.size() << " candidates." << endl;

	filename = "./ThLsh/cant_" + NumberToString(QueryID) + ".txt";
	fp = fopen(filename.c_str(), "w");
	for(set <unsigned>::iterator it = candidates.begin(); it != candidates.end(); ++it)
		fprintf(fp, "%d\n", *it);
	candidates.clear();
	fclose(fp);
*/
    

	return 0;
}
