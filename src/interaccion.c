#include "general.h"
#include "interaccion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

double pair_force(double r2, double* F_mod)
{
	double r6 = r2*r2*r2;
	double rc2 = 2.5*2.5;
	
	//sigma = epsilon = 1
	F_mod = 24.0*(2.0/r6 - 1.0)/(r6 + r2);
	return 0;
}

double forces(double* dx_vector, double* F_mod, int N)
{
	int i, j, k;
	double r2;
	
	for(i = 0; i < N - 1; i++)
	{
		for(j = i + 1; j < N; j++)
		{
			//Calcula el módulo de la fuerza de a pares, para la partícula i con todas las partículas j
			delta_x(x1, x2, L, dx_vector);
			r2 = norma2(dx_vector);
			pair_force(r2, F_mod);
			
			//Calcula la dirección de la fuerza resultante de i con todas las partículas j
			for(k = 0; k < 3; k++)
			{
				f[3*i+k] += F_mod*dx_vector[k];
				f[3*j+k] -= F_mod*dx_vector[k];
			}
		}
	}	
}
