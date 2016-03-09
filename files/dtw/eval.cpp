/*
	trajectory id  and trajectory filename are read from the q.txt file;

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

int main(int argc, char * argv[])
{
    /*
	int num = atoi(argv[1]);
	string dtw = argv[2];
	string lsh = argv[3];
     */
    
    int num;
    char trajid[20];
    char trajname[20];

 
	int i(0), id;
	char temp[50];
	vector <int> DTWResult;
	vector <int> LSHResult; 
	FILE *fp;
	FILE *fp2;
	vector <int>::iterator it;
	int count(0);
    string dtwname, lshname;
	
    FILE *file = fopen("q.txt", "r");
    
    while(fscanf(file, "%d %s %s\n", &num, trajid, trajname) != EOF)
    {
        dtwname = "./RateResult/candidate_"+ string(trajname) + "sort";
        lshname = "../newlsh/RhpLsh/cant_" + string(trajid) + ".txt";
        //cout << dtwname << endl;
        //cout << lshname << endl;
    
        count = 0;
	//read first num id from the sorted.txt to form the DTWResult
	fp = fopen(dtwname.c_str(), "r");
	for(i = 0; i < num; i++)
	{
		fscanf(fp, "%d %s\n", &id, temp);
		DTWResult.push_back(id);
	}
	fclose(fp);

	fp2 = fopen(lshname.c_str(), "r");
	while(fscanf(fp, "%d\n", &id)!=EOF)
	{
        //cout << id <<endl;
		LSHResult.push_back(id);
	}

	//cout << "LSH Result has " << LSHResult.size() << " elements" << endl;


	for(i = 0; i < num; i++)
	{
	//	cout << "No." << i << " : " << DTWResult[i] << endl;
		it = find(LSHResult.begin(), LSHResult.end(), DTWResult[i]);
		//cout << "it = " << *it << endl;
		if(it != LSHResult.end())
			count++;
	}

	//cout << "count = " << count << endl;
	double Accuracy = (double)count/num;
	//cout << "Accuracy = " << Accuracy << endl;
	cout << trajid << " " << LSHResult.size() << " " << Accuracy << endl;
        
        LSHResult.clear();
        DTWResult.clear();

    }
	return 0;
}
