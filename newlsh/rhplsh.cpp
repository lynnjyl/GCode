#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include "lsh.h"
#include <sys/time.h>
using namespace std;

/*struct element
{
    int gid;
    double val;
};*/


double wallclock(void) 
{
	struct timeval tv;
	struct timezone tz;
	double t;
	gettimeofday(&tv, &tz);
	t = (double)tv.tv_sec*1000;
	t += ((double)tv.tv_usec)/1000.0;
	return t;
}


int main(int argc, char * argv[])
{
    int mode = atoi(argv[1]);
    FILE *fp;
    if(mode == 1)
        fp = fopen("../../matrix_sub.txt", "r");
    else
        fp = fopen("../../matrix_sub_normalize.txt", "r");
    int TrajID, GridID;
    double value;
    
    int size = 1205401; // record the grid information 1-1205400
    vector <double> traj;   // For each trajectory in LSH;
    traj.resize(size);
    int numoftraj=131247;
    
    vector < vector <element> > matrix;
    matrix.resize(numoftraj);   // record trajectories 1-14939
    element ele;

    //int queryid = atoi(argv[1]);
    int queryid;
    
    double t1 = wallclock();
    //read the matrix into matrix;
    while(fscanf(fp, "%d %d %lf\n", &TrajID, &GridID, &value) != EOF)
    {
        ele.gid = GridID;
        ele.val = value;
        matrix[TrajID].push_back(ele);
    }
    fclose(fp);
    double t2 = wallclock();
    
    rhpLsh rhplsh;
    Parameter_rhplsh param_rhp;
    param_rhp.M = atoi(argv[2]);                 // hash table size
    param_rhp.L = atoi(argv[3]);                        // number of hash tables
    param_rhp.D = size;                 // dimension
    param_rhp.N = atoi(argv[4]);                        // binary code byte
    rhplsh.reset(param_rhp);
    cout << "Success in rhplsh" << endl;


 /*    for(int i = 1; i < numoftraj; i++)
     {
         cout << i << endl;
         fill(traj.begin(), traj.end(), 0);
         for(int j = 0; j < matrix[i].size(); j++)
         {
             traj[matrix[i][j].gid] = matrix[i][j].val;
         }
         rhplsh.insert(i, traj); 
     }*/

    for(int i = 1; i < numoftraj; i++)
    {
        //cout  << i << endl;
        rhplsh.insert(i, matrix[i]);
    }
  //  cout << "finished" << endl;
double t3 = wallclock();   


    set <unsigned> candidates;
    //int queryid = 1;
   /* for(int j = 0; j < matrix[queryid].size(); j++)
    {
        traj[matrix[queryid][j].gid] = matrix[queryid][j].val;
    }*/
    
    string filename;
    
    FILE *fp2 = fopen("query1.txt", "r");
    
    while(fscanf(fp2, "%d", &queryid) != EOF)
    {
        candidates = rhplsh.query(matrix[queryid]);
        //double t4 = wallclock();
        cout << "traj " << queryid << " has " << candidates.size() << " candidates." << endl;
        cout << queryid << " " << candidates.size() << endl;
        //filename = "./RhpLsh/cant_" + to_string(queryid)  + ".txt";
        filename = "./cant_" + to_string(queryid) + ".txt";
        fp = fopen(filename.c_str(), "w");  //cout << "fileopen" << endl;
        for(set <unsigned>::iterator it = candidates.begin(); it != candidates.end(); ++it)
            fprintf(fp, "%d\n", *it);
        //cout << "finish writing" << endl;
        
        fclose(fp);
        
        fp = fopen("result.txt", "a");
        fprintf(fp, "%d %lu\n", queryid, candidates.size());
        fclose(fp);
        candidates.clear();
	
	//cout << "*********************************" << endl;
//	cout << "Read matrix time: " << t2 - t1 << endl;
//	cout << "create hash tables: " << t3 - t2 << endl;
//	cout << "query time : " << t4 - t3 << endl;
//	cout << "*********************************" << endl;

    }
    cout << "finished " << endl;
    return 0;
}
