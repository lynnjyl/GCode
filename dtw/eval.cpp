/*
	argv[1]: the number of trajectories selected from the sorted file.
	argv[2]: sorted file produced from dtw process.
	argv[3]: LSH result.

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char * argv[])
{
	int num = atoi(argv[1]);
	string dtw = argv[2];
	string lsh = argv[3];
	int i(0), id;
	char temp[50];
	vector <int> DTWResult;
	vector <int> LSHResult; 
	FILE *fp;
	FILE *fp2;
	vector <int>::iterator it;
	int count(0);
	
	//read first num id from the sorted.txt to form the DTWResult
	fp = fopen(dtw.c_str(), "r");
	for(i = 0; i < num; i++)
	{
		fscanf(fp, "%d %s\n", &id, temp);
		DTWResult.push_back(id);
	}
	fclose(fp);

	fp2 = fopen(lsh.c_str(), "r");
	while(fscanf(fp, "%d\n", &id)!=EOF)
	{
		LSHResult.push_back(id);
	}


	for(i = 0; i < num; i++)
	{
		it = find(LSHResult.begin(), LSHResult.end(), DTWResult[i]);
		if(it != LSHResult.end())
			count++;
	}

	cout << "count = " << count << endl;
	double Accuracy = (double)count/num;
	cout << "Accuracy = " << Accuracy << endl;

	return 0;
}