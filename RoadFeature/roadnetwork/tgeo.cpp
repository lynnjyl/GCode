// transfer edge_grid.txt to grid_edge.txt
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
//#include <stdio.h>
//#include <string.h>
using namespace std;
int main(int argc, char * argv[])
{
	int count = atoi(argv[1]);
	ifstream ifs("edge_grid.txt");
	string str;
	vector < vector <int> > gid_eid(count+1);
//	memset(gid_eid, 0, 4*count);
//	cout << gid_eid[9][3] << endl;
	int p1, p2, p3;
	int eid;
	vector <int> gid_temp;
	int temp;
	p2 = 1;
	int max = 0;
	int ncount = 0;

	for(int i = 0; i < 433391; i++)
	{
	//	cout << "hello!" << i << endl;
		getline(ifs, str, '\n');
	//	cout << str << endl;
		p1 = str.find(' ', 0);
		eid = atoi(str.substr(0, p1++).c_str());
		ncount = 0;	
		while(p2 > 0)
		{
			p2 = str.find(' ', p1);
			temp = atoi(str.substr(p1, p2-p1).c_str());
			gid_eid[temp].push_back(eid);
			p1 = p2 + 1;	
			ncount++;
		}
		p2 = 1;
		
	}
	cout << "ok" << endl;
	int j;
	ofstream ofs("grid_edge.txt", ios::out);
	cout << "write file" << endl;
	for(int i = 1; i < count+1; i++)
	{
		ofs << i;
		for(int j; j < gid_eid[i].size(); j++)
			ofs << " " << gid_eid[i][j];
		ofs << endl;
	}
	
}
