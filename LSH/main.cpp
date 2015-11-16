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

	//apply the signature matrix to rbslsh.
/*
	for(j = 0; j < SigSize; j++)
	{
		cout << Sigmatrix[1][j] << " ";
	}
	cout << endl;
	for(j = 0; j < SigSize; j++)
	{
		cout << Sigmatrix[10][j] << " ";
	}
	cout << endl;
*/
	rbsLsh mylsh;
	Parameter param;
	param.M = 1024;              // Hash table size
    param.L = 5;                // Number of hash tables
    param.D = SigSize;    		// Dimension of the vector, it can be obtained from the instance of Matrix
    param.C = Dim; //×î´óÖµ       // The Difference between upper and lower bound of each dimension
    param.N = 20;               // Binary code bytes
    mylsh.reset(param);
    std::cout << "Success" << std::endl;

    //unsigned int data[Dim];	
    //int index, i, k;
   //memset(data, 0, Dim);

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


/*

	std::cout << maxid << std::endl;
	rbsLsh mylsh;
	Parameter param;
	param.M = 521;              // Hash table size
    param.L = 5;                // Number of hash tables
    param.D = Dim;    		// Dimension of the vector, it can be obtained from the instance of Matrix
    param.C = 2; //×î´óÖµ       // The Difference between upper and lower bound of each dimension
    param.N = 20;               // Binary code bytes
    mylsh.reset(param);
    std::cout << "Success" << std::endl;

    unsigned int data[Dim];	
    int index, i, k;
   //memset(data, 0, Dim);

    for(i = 0; i < matrix.size(); i++)
    {
    	//std::cout << "Trajectory ID: " << i << std::endl;
    	memset(data, 0, Dim);
    	//std::cout << "memory set" << std::endl;
    	//std::cout << "matrix[i].size: " << matrix[i].size() << std::endl;
    	for(k = 0; k < matrix[i].size(); k++)
    	{
    		index = matrix[i][k];
    		//std::cout << k << " " << index << std::endl;
    		data[index] = 1;
    	}
    	
    	mylsh.insert(i, data, Dim);
    }

    mylsh.query(data);

*/
    //random shuffle

    
	



    //printf("%d\n", matrix[TrajID].size());

   /* std::cout << matrix[TrajID][1] << " ";
    for(int i = 0; i < matrix[TrajID].size(); i++)
    {
    	std::cout << matrix[TrajID][i] << " ";
    	index = matrix[TrajID][i];
    	data[index] = 1;
    }*/

	return 0;
}