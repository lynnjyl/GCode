#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "lsh.h"

using namespace std;

struct element
{
    int gid;
    double val;
};

int main(int argc, char * argv[])
{
    FILE *fp = fopen("../../matrix.txt", "r");
    int TrajID, GridID;
    double value;
    
    int size = 1205401; // record the grid information 1-1205400
    vector <double> traj;   // For each trajectory in LSH;
    traj.resize(size);
    
    vector < vector <element> > matrix;
    matrix.resize(14940);   // record trajectories 1-14939
    element ele;
    
    
    //read the matrix into matrix;
    while(fscanf(fp, "%d %d %lf\n", &TrajID, &GridID, &value) != EOF)
    {
        ele.gid = GridID;
        ele.val = value;
        matrix[TrajID].push_back(ele);
    }
    fclose(fp);
    
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>psdlsh part
    /*psdLsh psdlsh;*/
     psdLsh psdlsh;
     Parameter_psdlsh param_psd;
     param_psd.M = atoi(argv[1]);        // Hash table size
     param_psd.L = atoi(argv[2]);           // Number of Hash tables
     param_psd.D = size;        // Dimenson of the vector.
     param_psd.T = GAUSSIAN;
     param_psd.W = atoi(argv[3]);         // window size
     psdlsh.reset(param_psd);
     std::cout << "Success in psdlsh" << std::endl;
     
     for(int i = 1; i < 14940; i++)
     {
         //cout << i << endl;
         //memset(&traj, 0, size);
         fill(traj.begin(), traj.end(), 0);
         //cout << "there are " << matrix[i].size() << " elements  in trajectory" << i << endl;
         for(int j = 0; j < matrix[i].size(); j++)
         {
             traj[matrix[i][j].gid] = matrix[i][j].val;
         }
         psdlsh.insert(i, traj);
     }
    cout << "finished" << endl;
    
    set <unsigned> candidates;
    int queryid = 12602;
    for(int j = 0; j < matrix[queryid].size(); j++)
    {
        traj[matrix[queryid][j].gid] = matrix[queryid][j].val;
    }
    candidates = psdlsh.query(traj);
    cout << "traj " << queryid << " has " << candidates.size() << " candidates." << endl;

    string filename = "./PsdLsh/cant_" + string(argv[1]) + "_" + argv[2]+ "_" + argv[3]+".txt";
    
    fp = fopen(filename.c_str(), "w");
    for(set <unsigned>::iterator it = candidates.begin(); it != candidates.end(); ++it)
        fprintf(fp, "%d\n", *it);
    candidates.clear();
    fclose(fp);

//     candidates = psdlsh.query(Sigmatrix[QueryID]);
//     cout << "traj " << QueryID << " has " << candidates.size() << " candidates." << endl;
//     
//     filename = "./PsdLsh/cant_" + NumberToString(QueryID) + ".txt";
//     fp = fopen(filename.c_str(), "w");
//     for(set <unsigned>::iterator it = candidates.begin(); it != candidates.end(); ++it)
//     fprintf(fp, "%d\n", *it);
//     candidates.clear();
//     fclose(fp);

    
    
    return 0;
}