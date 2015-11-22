#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;


struct st
{
	int id;
	int times;
};

int main(int argc, char * argv[])
{

	FILE *fp = fopen(argv[1], "r");
	int num = atoi(argv[2]);
	st *sttemp = new st [num]
	int i = 0;;
	//int *numbers = new int [num];
	int id1, id2;
	double rate;

	memset(numbers, 0, num*sizeof(int)*2);
	//int max = 0, maxid = 0;

	while(fscanf(fp, "%d %d %lf\n", &id1, &id2,&rate)!= EOF)
	{

		//numbers[id1]++;
	}	

	for(i = 1; i < num; i++)
	{
		if(numbers[i] > max)
		{
			max = numbers[i];
			maxid = i;
		}		
	}

	cout << maxid << ": " << max << endl;
	




	return 0;
}