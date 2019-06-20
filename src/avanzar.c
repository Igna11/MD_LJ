#include "general.h"
#include "interaccion.h"
#include "avanzar.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Definicion de funciones

double velocity_verlet(double* x, double* v, double* f, double* F_mod, double h, double L, int N)
{
	// f es el vector que genera forces afuera de esta funcion y que le damos como dato
	int i;
	for(i = 0; i<3*N; i++)
	{
		x[i] = x[i] + v[i]*h + 0.5*f[i]*h*h/m; // Esto quisiera ser x(t+h) - Se actualizan posiciones en un paso entero
		v[i] = v[i] + 0.5*f[i]*h; // Esto quisiera ser v(t+h/2). - Se actualiza en medio paso la velocidad
	}
	
	// Con las nuevas posiciones se calculan las nuevas fuerzas
	forces(dx_vector, F_mod, f, x, N, L); // Esto define f(t+h)

	// Con las nuevas fuerzas calculo el medio paso que faltaba para terminar de actualizar las velocidades
	for(i = 0; i<3*N; i++)
	{
		v[i] = v[i] + 0.5*f[i]*h // Esto quisiera ser v(t+h)
	}
		
	return 0.0;
}