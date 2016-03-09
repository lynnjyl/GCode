#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;

int main(int argc, char * argv[])
{
	FILE * fp;
	fp = fopen("20081023025304.plt", "r+");
	float lat, longt, time;
	char str[200], date[30];
	int p1, p2;

	for(int i = 0; i < 6; i++)
	{
        fscanf(fp, "%*[^\n]%*c");
	}
    fscanf(fp,"%s\n", str);
    printf("%s\n", str);
    sscanf(str, "%f,%f,%i,%i,%f,%s", &lat, &longt, &p1, &p2, &time, date);
    cout << "latitude: " << lat << endl;
    cout << "longitude: " << longt << endl;
    cout << "time: " << time << endl;

	fclose(fp);

	return 0;
}
