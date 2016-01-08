
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

int main(int argc, char * argv[])
{
    
	/*int num = atoi(argv[1]);
	string dtw = argv[2];
	string file = argv[3];*/
	 int num;
    	char trajid[20];
    	char trajname[20];
    	string dtw, file1, file2;

    
    	FILE *fp1, *fp2, *fp;
	//FILE *fp2;
	int i(0), id;
	char temp[50];
	vector <int>::iterator it;
	vector <int> DTWResult;
	vector <int> CResult, PResult; 

	FILE *f = fopen(argv[1], "r");
	int count1(0), count2(0);
        	//count = 0;

 while(fscanf(f, "%d %s %s\n", &num, trajid, trajname) != EOF)
    {
        dtw = "../../dtw/RateResult/candidate_"+ string(trajname) + "sort";
        file1 = "./result/" + string(trajid) + "_cosine_sort";
        file2 = "./result/" + string(trajid) + "_product_sort";
        count1 = count2 = 0;
	//read first num id from the sorted.txt to form the DTWResult
	fp = fopen(dtw.c_str(), "r");
	fp1 = fopen(file1.c_str(), "r");
	fp2 = fopen(file2.c_str(), "r");
	for(i = 0; i < num; i++)
	{
		fscanf(fp, "%d %s\n", &id, temp);
		DTWResult.push_back(id);
		fscanf(fp1, "%d %s\n", &id, temp);
		CResult.push_back(id);
		fscanf(fp2, "%d %s\n", &id, temp);
		PResult.push_back(id);
	}
	fclose(fp);
	fclose(fp2);
	fclose(fp1);


	for(i = 0; i < num; i++)
	{
		it = find(CResult.begin(), CResult.end(), DTWResult[i]);
		if(it != CResult.end())
			count1++;
		it = find(PResult.begin(), PResult.end(), DTWResult[i]);
		if(it != PResult.end())
			count2++;
	}


	DTWResult.clear();
	PResult.clear();
	CResult.clear();

	cout << "*********************************" << endl;
	cout << "Traj ID = " << trajid << " Traj Name = " << trajname << endl;
	cout << "cosine count = " << count1 << endl;
	double Accuracy = (double)count1/num;
	cout << "Cosine Accuracy = " << Accuracy << endl;
	cout << "product count = " << count2 << endl;
	Accuracy = (double)count2/num;
	cout << "Product Accuracy = " << Accuracy << endl;

}
	
	return 0;
}
