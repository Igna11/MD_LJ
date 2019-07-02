#include "general.h"
#include "interaccion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

double pair_force(double* F_mod, double r2)
{
	/*
	Esta funcion calcula el modulo de la fuerza de interaccion dado un potencial de Lenard Jones.
	El double F_mod que le damos es para que lo rellene con ese valor.
	Además, calcula el valor de la energia potencial y lo devuelve.
	*/
	double r6 = r2*r2*r2;
	double V; 
	
	//sigma = epsilon = 1
	F_mod[0] = 24.0*(2.0/r6 - 1.0)/(r6 * r2);
	V = 4.0*(1.0/r6)*((1.0/r6)-1);
	return V;
}

double forces(double* dx_vector, double* F_mod, double* f, double* x, double L, int N)
{
	int i, j, k;
	double r2, V;
	double rc2 = 2.5*2.5; //el radio de corte standar al cuadrado (definido así)
	//RESETEA f
	for(i = 0; i < 3*N; i++)
	{
		f[i] = 0;
	}
	
	V = 0;
	for(i = 0; i < (N - 1);  i++)
	{
		for(j = i + 1; j < N; j++)
		{
			//Calcula el módulo de la fuerza de a pares, para la partícula i con todas las partículas j
			delta_x((x+3*i), (x+3*j), dx_vector, L);			
			r2 = norma2(dx_vector);
			
			if(r2 < rc2) 
			{
				V += pair_force(F_mod, r2);
				
				//Calcula la dirección de la fuerza resultante de i con todas las partículas j
				for(k = 0; k < 3; k++)
				{
					f[3*i+k] += F_mod[0]*dx_vector[k];
					f[3*j+k] -= F_mod[0]*dx_vector[k];
				}
				
			}
			
			// Reinicio F_mod 
			// F_mod[0] = 0.0; 
		}
	}
	return V;
}
