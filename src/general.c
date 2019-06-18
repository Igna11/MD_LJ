#include "general.h"
#include "stdlib.h"
double random()
{
	return ((double)rand()) / ((double) RAND_MAX);
}

double gaussiana(double mu, double sigma)
{
	int n = 10;
	double z = 0;
	
	for(int i = 0; i<n; i++)
	{
		z += random();
	}
	z = sqrt(12*n)*(z/n - 0.5);
	return z*sigma+mu;
}

double norma2(double* ri, double* rj, int n)
{
	int i;
	double norma = 0;
	for(i = 0; i<n; i++)
	{
		norma += (ri[i]-rj[i])*(ri[i]-rj[i]);
	}
	norma = pow(norma,0.5);
	return norma;
}

double delta_x(double x1, double x2, double L)
{
	double delta = x1 - x2;
	if(delta < -L/2)
	{
		delta = delta + L;
	}
	else if(delta > L/2)
	{
		delta = delta - L;
	}
	return delta;
}