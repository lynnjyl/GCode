#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <ctime>
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

int main(int argc, char * argv[])
{
	FILE *fp = fopen("matrix.txt", "r");
	int TrajID, GridID, i, j, k, CurrentTraj(1);
	int Dim(488600), NumofTraj(18671);
	int SigSize = atoi(argv[1]);
	int bands = atoi(argv[2]);
	int maxid = 0, num = 0;
	vector <int> pi;					//vector for min-hashing
	vector < vector<int> > matrix;
	//unsigned Sigmatrix[NumofTraj][SigSize];
	vector < vector<unsigned> > Sigmatrix;
	int minhash;
	matrix.resize(NumofTraj);
	pi.resize(Dim);
	Sigmatrix.resize(NumofTraj);

	cout << "size of pi : " << sizeof(pi) << endl;
	cout << "size of matrix : " << sizeof(matrix) << endl;
	cout << "size of Sigmatrix : " << sizeof(Sigmatrix) << endl;
	//cout << "begin " << endl;
	
	// set pi array
	for(i = 0; i < Dim; i++)
		pi[i] = i;
///////////////////////////////////////////////////////////////////
	//get the trajectory matrix
	while(fscanf(fp, "%d %d\n", &TrajID, &GridID) != EOF)
		matrix[TrajID].push_back(GridID);
	
	cout << "read finished" << endl;
	//get signature matrix
	for(j = 0; j < SigSize; j++)
	{
		RandomShuffle(pi);
		for(k = 0; k < NumofTraj; k++)
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
	cout << "get sigmatrix" << endl;
//////////////////////////////////////////////////////////////////////////

	
	matrix.clear();
	for(j = 0; j < NumofTraj; j++)
		vector <int>().swap(matrix[i]);

/*	// rbslsh
	rbsLsh mylsh;
	Parameter_rbslsh param;
	param.M = 521;              // Hash table size
    param.L = 5;                // Number of hash tables
    param.D = SigSize;    		// Dimension of the vector, it can be obtained from the instance of Matrix
    param.C = Dim; //×î´óÖµ       // The Difference between upper and lower bound of each dimension
    param.N = 20;               // Binary code bytes
    mylsh.reset(param);
    std::cout << "Success" << std::endl;


    for(i = 0; i < NumofTraj; i++)
    {
    	mylsh.insert(i, Sigmatrix[i]);
    }
    cout << "ok" << endl;

    set <unsigned> candidates;
    for(i = 0; i < NumofTraj; i++)
    {
    	candidates = mylsh.query(Sigmatrix[i]);
    	cout << "traj " << i << "has " << candidates.size() << " candidates." << endl;
    	candidates.clear();
    }
*/

    //psdlsh
    psdLsh psdlsh;
    Parameter_psdlsh param_psd;
    param_psd.M = 521;
    param_psd.L = 5;
    param_psd.D = SigSize;
    param_psd.T = GAUSSIAN;
    param_psd.W = 0.5;
    psdlsh.reset(param_psd);
    std::cout << "Success" << std::endl;

    for(i = 0; i < NumofTraj; i++)
    {
    	psdlsh.insert(i, Sigmatrix[i]);
    }
    cout << "ok" << endl;

    set <unsigned> candidates;
    for(i = 0; i < NumofTraj; i++)
    {
    	candidates = psdlsh.query(Sigmatrix[i]);
    	cout << "traj " << i << "has " << candidates.size() << " candidates." << endl;
    	candidates.clear();
    }

	return 0;
}