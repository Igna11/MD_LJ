#include "general.h"
#include "interaccion.h"
#include "avanzar.h"
#include "traductor.h"
#include "inicializar.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/* NECESITAMOS QUE AFUERA ESTEN DEFINIDOS

	
*/


double velocity_Verlet(double *x,double *v, double *f, int N, double h, double L)
{	
	double *dx_vector = (double *) malloc(3*sizeof(double)); //vector distancia entre un par de partículas (la menor entre la distancia con la partícula real y la partícula imagen)
	double *F_mod = (double *) malloc(sizeof(double));; //puntero con el módulo de la fuerza, se va reescribiendo all the time
	
	for(i = 0; i < 3; i++)
	{
		dx_vector[i] = 0;
	}
	F_mod[0] = 0.0;
	
	E_pot = velocity_verlet(x, v, dx_vector, f, F_mod, h, L, N)
	
	free(F_mod);
	free(dx_vector);

	return E_pot/(double) N;
}

double inicializar(double *x, double *v,double *f, int N, double L, double T)
{
	set_x(x, L, N);
	set_v(v, T, N);
	forces(dx_vector, F_mod, f, x, L, N);

	return 0;
}

