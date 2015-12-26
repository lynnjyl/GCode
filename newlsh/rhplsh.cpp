#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include "lsh.h"

using namespace std;

/*struct element
{
    int gid;
    double val;
};*/

int main(int argc, char * argv[])
{
    FILE *fp = fopen("../../matrix_sub.txt", "r");
    int TrajID, GridID;
    double value;
    
    int size = 1205401; // record the grid information 1-1205400
    vector <double> traj;   // For each trajectory in LSH;
    traj.resize(size);
    int numoftraj=131247;
    
    vector < vector <element> > matrix;
    matrix.resize(numoftraj);   // record trajectories 1-14939
    element ele;

    int queryid = atoi(argv[1]);
    
    
    //read the matrix into matrix;
    while(fscanf(fp, "%d %d %lf\n", &TrajID, &GridID, &value) != EOF)
    {
        ele.gid = GridID;
        ele.val = value;
        matrix[TrajID].push_back(ele);
    }
    fclose(fp);
    
    rhpLsh rhplsh;
    Parameter_rhplsh param_rhp;
    param_rhp.M = 1000;                 // hash table size
    param_rhp.L = 5;                        // number of hash tables
    param_rhp.D = size;                 // dimension
    param_rhp.N = 6;                        // binary code byte
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
    cout << "finished" << endl;
    
    set <unsigned> candidates;
    //int queryid = 1;
   /* for(int j = 0; j < matrix[queryid].size(); j++)
    {
        traj[matrix[queryid][j].gid] = matrix[queryid][j].val;
    }*/
    
    string filename;
    candidates = rhplsh.query(matrix[queryid]);
    cout << "traj " << queryid << " has " << candidates.size() << " candidates." << endl;
    filename = "./RhpLsh/cant_" + to_string(queryid)  + ".txt";
    fp = fopen(filename.c_str(), "w");
    for(set <unsigned>::iterator it = candidates.begin(); it != candidates.end(); ++it)
        fprintf(fp, "%d\n", *it);
    candidates.clear();
    fclose(fp);

    return 0;
}
