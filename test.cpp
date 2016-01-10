/*
	get the max number of elements in one vector of the matrix
*/

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	FILE *fp = fopen("../matrix_sub_gm.txt", "r");

	int max(0), temp(0), maxid(0);
	int i(0);
	int trajid, gid, current(0), count(0);
	double value;

	while(fscanf(fp, "%d %d %lf\b", &trajid, &gid, &value) != EOF)
	{
		if(trajid != current)
		{
			if(count > max)
			{
				max = count;
				maxid = current;
			}
			cout << current << ": " << count << endl;
			count = 1;
			current = trajid;
		}
		else
			count++;
	}
	cout << "max = " << max << endl;
	cout << "maxid = " << maxid << endl;


	return 0;
}