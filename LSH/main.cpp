#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
//#include "lsh.h"

int main()
{
	/*FILE *fp = fopen("matrix.txt", "r");
	int TrajID, GridID;
	int Dim = 488600;;
	int maxid = 0, num = 0;;
	std::vector < std::vector<int> > matrix;
	matrix.resize(18671);

	while(fscanf(fp, "%d %d\n", &TrajID, &GridID) != EOF)
	{
		matrix[TrajID].push_back(GridID);
		if(maxid <= GridID)
		{
			//num++;
			maxid = GridID;
		}
	}



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

    mylsh.query(data);*/


    //random shuffle

    int a[10];
    int i(0), r(0), temp(0);
    for(i = 0; i < 10; i++)
        a[i] = i;

    for(i = 0; i < 10; i++)
    {
        r = rand()%10;
        temp = a[i];
        a[i] = a[r];
        a[r] = temp; 
    }

    for(i = 0; i < 10; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;
	



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