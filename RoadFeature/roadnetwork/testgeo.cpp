// test the maximum number of features of one edges

//#include <stdio.h>
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

int GetGID(double lat, double lng)
{
    //the map is divided into 10x10 grids
    int x, y;
    x = (lat - minlat)/0.17 + 1;
    y = (lng - minlng)/0.23;
    return 10*y+x;
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
    
    //cout << "=================================" << endl;
    //cout << "set size : " << gid.size() << endl;
    //set<int>::iterator it; //定义前向迭代器
    //中序遍历集合中的所有元素
    
    ofstream offs("edge_grid.txt", ios::out|ios::app);
    offs << eid;
    
    for(it = gid.begin(); it != gid.end(); it++)
    {
        int i = *it;
        offs << " " << i;
        idstr << i;
        string filename = "./geos/geos_" + idstr.str();
        cout << filename << endl;
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
    
    for (int i = 0; i < 433391; i++)
    {
        getline(ifs, str, '\n');
        GetInfo(str, eid, gid);
        
    }

}