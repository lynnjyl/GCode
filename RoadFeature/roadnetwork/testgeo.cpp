// test the maximum number of features of one edges

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
using namespace std;
double minlat = 39.4;
double minlng = 115.3;
double maxlat = 41.1;
double maxlng = 117.6;
double differ = 0.05;
string differstr = "0.05";
int GetGID(double lat, double lng)
{
        //the map is divided into grids
        int para = (maxlat - minlat)/differ + 1;
        int x, y;
        x = (lat - minlat)/differ + 1;
        y = (lng - minlng)/differ;
        return para*y+x;
}

void GetInfo(string str, int &eid, set <int> gid)
{
    int p1, p2, p3 = 1;
    double lat, lng;
    int gid_temp;
    int length = str.length();
    set<int>::iterator it;
    stringstream idstr;
    p1 = str.find('\t', 0);
    //cout << str << endl;
    eid = atoi(str.substr(0, p1++).c_str());
    //cout << eid << endl;
    while (p3 > 0)
    {
        p2 = str.find('\t', p1);    //cout << "p2: " << p2 << endl;
        p3 = str.find('\t', p2+1);  //cout << "p3: " << p3 << endl;
        
        lat = atof(str.substr(p1, p2-p1).c_str());
        p2++;

        lng = atof(str.substr(p2, p3-p2).c_str());
        //cout << lat << " " << lng << endl;
        p1 = p3+1;
        gid_temp = GetGID(lat, lng);
        //cout << "gid = " << gid_temp << endl;
        gid.insert(gid_temp);
    }
       
	string name = "edge_grid_" + differstr + ".txt";
    ofstream offs(name.c_str(), ios::out|ios::app);
    offs << eid;
    
    for(it = gid.begin(); it != gid.end(); it++)
    {
        int i = *it;
        offs << " " << i;
        idstr << i;
        string filename = "./geos/geos_" + idstr.str();
       // cout << filename << endl;
        ofstream ofs(filename.c_str(), ios::out|ios::app);
        ofs << str;
        ofs.close();
        idstr.str("");
    }
    offs << endl;
    offs.close();
    
    
    
    
//    if(gid.size() > 1)
//    {
//        cout << eid << " ";
//        for(it = gid.begin(); it != gid.end(); it++)
//            cout << *it << " ";
//        cout << endl;
//    }
    //cout << lat << " " << lng << endl;
    //cout << "p2: " << p2 << endl;
    //cout << str.substr(p1, p2-p1) << endl;
    //while(p2)
    //{
        
    //}

}

int main(int argc, char * argv[])
{
    ifstream ifs("geos.txt");
    string str;
    set <int> gid;
    int eid;
	int size = ((maxlat - minlat)/differ + 1) * ((maxlng - minlng)/differ + 1);
	cout << "there are " << size << " grids" << endl;    
    for (int i = 0; i < 433391; i++)
    {
        getline(ifs, str, '\n');
        GetInfo(str, eid, gid);
        
    }

}
