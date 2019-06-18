#include "general.h"
#include "interaccion.h"
#include "avanzar.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Definicion de funciones

double velocity_verlet(double* x, double* v, double* f, double h, double m)
{
	int i;
	for(i = 0; i<3*N; i++)
	{
		x[i] = x[i] + v[i]*h + 0.5*f[t]*h*h/m; // Esto quisiera ser x(t+h)
		v[i] = v[i] + 0.5*(f[i]+f(t+h))*h/m; // Esto quisiera ser v(t+h). COMO SE CALCULA F(T+H)? Si es en efecto como x(t+h) y v(t+h) que estamos redefiniendo, entonces se pierde la informacion de f(t) si ya reescribo f(t+h)
	}
	return 0.0
}