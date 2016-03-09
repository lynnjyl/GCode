#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;


int main(int argc, char *argv[])
{
    FILE *fp = fopen("analysis.txt", "r");

    int id, num;
    int size = atoi(argv[1]);
    int sum[size];
    memset(sum, 0, size);

    cout << "begin to read" << endl;
    while(fscanf(fp, "%d %d\n", &id, &num) != EOF)
    {
        //cout << id << " " << num << endl;
        if(id > 0 && id < size)
            sum[id] += num;
    }

    fclose(fp);

    cout << "read finished" << endl;

    FILE *fp2 = fopen("result.txt", "w");

    for(unsigned int i = 0; i < size; i++)
    {
        if(sum[i] != 0)
            fprintf(fp2, "%d %d\n", i, sum[i]);
    }


    return 0;
}
