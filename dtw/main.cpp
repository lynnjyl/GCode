/* sscanf example */
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <time.h>
using namespace std;

//20081023025304.plt

double TRAC1[20000][2];
double TRAC2[20000][2];
int nTRAC1, nTRAC2;
char f1[] = "20081023025304.plt";
char f2[] = "20090413213935.plt";

double m = 99999999;

double* DP;

double dist(int i,int j){
	double a = TRAC1[i][0] - TRAC2[j][0];
	double b = TRAC1[i][1] - TRAC2[j][1];
	return sqrt(a*a + b*b);
}

double DWT(){
	
	//double* DP =(double*) malloc(sizeof(double)*nTRAC1*nTRAC2);
	int i, j;
	double a, b, c;
	for (j = 1; j < nTRAC2; j++)
		*(DP + j) = 0;
	for (i = 1; i < nTRAC1; i++)
		*(DP + nTRAC2*i) = 0;
	// *(DP) = 0;

	for (i = 1; i < nTRAC1; i++)
		for (j = 1; j < nTRAC2; j++)
		{
			a = *(DP + nTRAC2*(i-1) + j);
			b = *(DP + nTRAC2*i + j-1);
			c = *(DP + nTRAC2*(i-1) + j-1);
			double mm = min(min(a,b),c);
			*(DP + nTRAC2*i + j) = dist(i, j) + mm;
			//printf("%lf %lf %lf\n", a, b, c);
			//system("pause");
			
			//printf("%lf\n", *(DP + nTRAC2*i + j));
		}
	double ans = *(DP + nTRAC2*(nTRAC1 - 1) + nTRAC2 - 1);
	//free(DP);
	return ans;
}

int main()
{
	nTRAC1 = 0, nTRAC2 = 0;

	FILE * pFile;
	char mystring[100];
	double x, y;
	pFile = fopen(f1, "r");
	if (pFile == NULL) perror("Error opening file");
	else {
		fgets(mystring, 100, pFile);
		fgets(mystring, 100, pFile);
		fgets(mystring, 100, pFile);
		fgets(mystring, 100, pFile);
		fgets(mystring, 100, pFile);
		fgets(mystring, 100, pFile);
		while (fgets(mystring, 100, pFile) != NULL)
		{
			//sscanf(mystring, "%s %*s %d", str, &i);
			sscanf(mystring, "%lf,%lf", &x, &y);
			//puts(mystring);
			//printf("%.6lf, %.6lf", x,y);
			TRAC1[nTRAC1][0] = x;
			TRAC1[nTRAC1][1] = y;
			nTRAC1++;
		}
		fclose(pFile);
	}

	pFile = fopen(f2, "r");
	if (pFile == NULL) perror("Error opening file");
	else {
		fgets(mystring, 100, pFile);
		fgets(mystring, 100, pFile);
		fgets(mystring, 100, pFile);
		fgets(mystring, 100, pFile);
		fgets(mystring, 100, pFile);
		fgets(mystring, 100, pFile);
		while (fgets(mystring, 100, pFile) != NULL)
		{
			//sscanf(mystring, "%s %*s %d", str, &i);
			sscanf(mystring, "%lf,%lf", &x, &y);
			//puts(mystring);
			//printf("%.6lf, %.6lf", x, y);
			TRAC2[nTRAC2][0] = x;
			TRAC2[nTRAC2][1] = y;
			nTRAC2++;
		}
		fclose(pFile);
	}


	DP = (double*)malloc(sizeof(double)*nTRAC1*nTRAC2);
	clock_t t;
	t = clock();

	printf("%.6lf\n",DWT());

	t = clock() - t;
	printf("It took me %f seconds.\n", ((float)t) / CLOCKS_PER_SEC);

	free(DP);
	//system("pause");

	return 0;
}
