#include <iostream>
#include <functional>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set> 
#include <sstream>

using namespace std;


template <typename T>
string NumberToString ( T Number )
{
	stringstream ss;
	ss << Number;
	return ss.str();
}
int main(int argc, char * argv[])
{
	/*int SigSize = atoi(argv[1]);
	int QueryID = atoi(argv[2]);

	int Dim(488600), NumofTraj(18671);
	vector < vector <unsigned> > Sigmatrix;
	vector < vector <int> > matrix;*/

	//int QueryID = atoi(argv[1]);
	int NumofTraj(18671), count(0);
	int start = atoi(argv[1]);
	int num = atoi(argv[2]);
	int TrajID, GridID, i, temp;
	vector < vector <int> > matrix;			
	FILE *fp = fopen("matrix.txt", "r");
	set <int> gid; 
	string filename;

	matrix.resize(NumofTraj);

	//cout << "begin to read" << endl;
	while(fscanf(fp, "%d %d\n", &TrajID, &GridID) != EOF)
	{
		//cout << TrajID << " " << GridID << endl;
		matrix[TrajID].push_back(GridID);
	}
	fclose(fp);
	//cout << "finish reading" << endl;

	FILE *fp2 = fopen("r.txt", "w");
	for(int j = start; j < num; j++)
	{
		for(i = 1; i < NumofTraj; i++)
		{
			count = 0;
			if(i != j)
			{
				for(vector <int>::iterator it = matrix[j].begin(); it != matrix[j].end(); ++it)
					gid.insert(*it);
				for(vector <int>::iterator it = matrix[i].begin(); it != matrix[i].end(); ++it)
					gid.insert(*it);

				vector <int>::iterator iter;
				for(vector <int>::iterator it = matrix[j].begin(); it != matrix[j].end(); ++it)
				{
					temp = *it;
					iter = find(matrix[i].begin(), matrix[i].end(), *it);
					if(iter != matrix[i].end())
						count++;
				}
				//cout << count << " " << gid.size() << endl;
				double similarity = (float)count/gid.size();
				if(similarity > 0.8)
				{
					cout << j << " " << i << " " << similarity << endl;
					fprintf(fp2, "%d %d %lf\n", j, i, similarity);
					//cout << "wrote" << endl;
				}
				gid.clear();
			}
		}
		
	}
	fclose(fp2);
	return 0;

}