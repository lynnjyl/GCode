#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;

int main(int argc, char * argv[])
{
	FILE * fp;
	fp = fopen("20081023025304.plt", "r+");
	double lat, longt, time;
	char str[80];
	int p1, p2;

	for(int i;i < 8; i++)
	{
		fscanf(fp,"%f,%f,%i,%i,%f,%c\n", &lat, &longt, &p1, &p2, &time, str);
		printf("%f,%f,%i,%i,%f,%c\n", lat, longt, p1, p2, time, str);
	}
	fclose(fp);

	return 0;
}
