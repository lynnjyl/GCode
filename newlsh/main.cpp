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
    matrix.resize(58181);   // record trajectories 1-14939
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
     psdLsh psdlsh, psdlsh1, psdlsh2, psdlsh3, psdlsh4;
     Parameter_psdlsh param_psd, param_psd1, param_psd2, param_psd3, param_psd4;
    ////////////////////////////////////////////////////
     param_psd.M = 1500;           // Hash table size
     param_psd.L = 5;           // Number of Hash tables
     param_psd.D = size;                    // Dimenson of the vector.
     param_psd.T = GAUSSIAN;
     param_psd.W = 0.5;           // window size
     psdlsh.reset(param_psd);
     std::cout << "Success in psdlsh" << std::endl;
    
    ////////////////////////////////////////////////////
    param_psd1.M = 1100;           // Hash table size
    param_psd1.L = 5;           // Number of Hash tables
    param_psd1.D = size;                    // Dimenson of the vector.
    param_psd1.T = GAUSSIAN;
    param_psd1.W = 0.5;           // window size
    psdlsh1.reset(param_psd1);
    std::cout << "Success in psdlsh" << std::endl;
    
    ////////////////////////////////////////////////////
    param_psd2.M = 1200;           // Hash table size
    param_psd2.L = 5;           // Number of Hash tables
    param_psd2.D = size;                    // Dimenson of the vector.
    param_psd2.T = GAUSSIAN;
    param_psd2.W = 0.5;           // window size
    psdlsh2.reset(param_psd2);
    std::cout << "Success in psdlsh" << std::endl;
    
    ////////////////////////////////////////////////////
    param_psd3.M = 1300;           // Hash table size
    param_psd3.L = 5;           // Number of Hash tables
    param_psd3.D = size;                    // Dimenson of the vector.
    param_psd3.T = GAUSSIAN;
    param_psd3.W = 0.5;           // window size
    psdlsh3.reset(param_psd3);
    std::cout << "Success in psdlsh" << std::endl;
    
    ////////////////////////////////////////////////////
    param_psd4.M = 1400;           // Hash table size
    param_psd4.L = 5;           // Number of Hash tables
    param_psd4.D = size;                    // Dimenson of the vector.
    param_psd4.T = GAUSSIAN;
    param_psd4.W = 0.5;           // window size
    psdlsh4.reset(param_psd4);
    std::cout << "Success in psdlsh" << std::endl;
    
     for(int i = 1; i < 14940; i++)
     {
         cout << i << endl;
         //memset(&traj, 0, size);
         fill(traj.begin(), traj.end(), 0);
         //cout << "there are " << matrix[i].size() << " elements  in trajectory" << i << endl;
         for(int j = 0; j < matrix[i].size(); j++)
         {
             traj[matrix[i][j].gid] = matrix[i][j].val;
         }
         psdlsh.insert(i, traj);
         psdlsh1.insert(i, traj);
         psdlsh2.insert(i, traj);
         psdlsh3.insert(i, traj);
         psdlsh4.insert(i, traj);
         
     }
    cout << "finished" << endl;
    
    set <unsigned> candidates;
    int queryid = 12602;
    for(int j = 0; j < matrix[queryid].size(); j++)
    {
        traj[matrix[queryid][j].gid] = matrix[queryid][j].val;
    }
    
    string filename;
    
    candidates = psdlsh.query(traj);
    cout << "traj " << queryid << " has " << candidates.size() << " candidates." << endl;
    filename = "./PsdLsh/cant_" + to_string(param_psd.M) + "_" + to_string(param_psd.L)+ "_" + to_string(param_psd.W)+".txt";
    fp = fopen(filename.c_str(), "w");
    for(set <unsigned>::iterator it = candidates.begin(); it != candidates.end(); ++it)
        fprintf(fp, "%d\n", *it);
    candidates.clear();
    fclose(fp);
    
    candidates = psdlsh1.query(traj);
    cout << "traj " << queryid << " has " << candidates.size() << " candidates." << endl;
    filename = "./PsdLsh/cant_" + to_string(param_psd1.M) + "_" + to_string(param_psd1.L)+ "_" + to_string(param_psd1.W)+".txt";
    fp = fopen(filename.c_str(), "w");
    for(set <unsigned>::iterator it = candidates.begin(); it != candidates.end(); ++it)
        fprintf(fp, "%d\n", *it);
    candidates.clear();
    fclose(fp);
    
    candidates = psdlsh2.query(traj);
    cout << "traj " << queryid << " has " << candidates.size() << " candidates." << endl;
    filename = "./PsdLsh/cant_" + to_string(param_psd2.M) + "_" + to_string(param_psd2.L)+ "_" + to_string(param_psd2.W)+".txt";
    fp = fopen(filename.c_str(), "w");
    for(set <unsigned>::iterator it = candidates.begin(); it != candidates.end(); ++it)
        fprintf(fp, "%d\n", *it);
    candidates.clear();
    fclose(fp);
    
    candidates = psdlsh3.query(traj);
    cout << "traj " << queryid << " has " << candidates.size() << " candidates." << endl;
    filename = "./PsdLsh/cant_" + to_string(param_psd3.M) + "_" + to_string(param_psd3.L)+ "_" + to_string(param_psd3.W)+".txt";
    fp = fopen(filename.c_str(), "w");
    for(set <unsigned>::iterator it = candidates.begin(); it != candidates.end(); ++it)
        fprintf(fp, "%d\n", *it);
    candidates.clear();
    fclose(fp);
    
    candidates = psdlsh4.query(traj);
    cout << "traj " << queryid << " has " << candidates.size() << " candidates." << endl;
    filename = "./PsdLsh/cant_" + to_string(param_psd4.M) + "_" + to_string(param_psd4.L)+ "_" + to_string(param_psd4.W)+".txt";
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
