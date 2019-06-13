#include "general.h"
#include "stdlib.h"
float random()
{
	return ((float)rand()) / ((float) RAND_MAX);
}

float gaussiana(float mu, float sigma)
{
	int n = 10;
	float z = 0;
	
	for(int i = 0; i<n; i++)
	{
		z += random();
	}
	z = sqrt(12)*(z/n - 0.5);
	return z*sigma+mu;
}

float norma2(float* ri, float* rj, int n)
{
	int i;
	float norma = 0;
	for(i = 0; i<n; i++)
	{
		norma += (ri[i]-rj[i])*(ri[i]-rj[i]);
	}
	norma = pow(norma,0.5);
	return norma;
}