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

double norma2(double* V)
{
	int i;
	double norma = 0;
	for(i = 0; i<3; i++)
	{
		norma += V[i]*V[i];
	}
	return norma;
}

double delta_x(double* x1, double* x2, double* dx, double L)
{
	/* 
	Esta función va a devolver en el vector dx (que le estamos dando para que _rellene_ la diferencia componente a componente entre los vectores x1 y x2.
	Incluir las condiciones acorde a L da la condicion periodica de borde.
	*/
	//Condicion periodica de contorno en los bordes
	int k;
	for(k = 0; k < 3; k++)
	{
		dx[k] = x1[k] - x2[k];
		if(dx[k] < -L/2)
		{
			dx[k] = dx[k] + L;
		}
		else if(dx[k] > L/2)
		{
			dx[k] = dx[k] - L;
		}
	}
	return 0;
}