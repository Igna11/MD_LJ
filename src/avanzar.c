#include "general.h"
#include "interaccion.h"
#include "avanzar.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Definicion de funciones

double velocity_verlet(double* x, double* v, double* dx_vector, double* f, double* F_mod, double h, double L, int N)
{
	// f es el vector que genera forces afuera de esta funcion y que le damos como dato
	int i;
	double V;
	double *v_mediopaso = (double *) malloc(3*N*sizeof(double)); 
	
	for(i = 0; i < 3*N; i++)
	{
		v_mediopaso[i] = 0.0;
	}

	for(i = 0; i<3*N; i++)
	{
		x[i] = x[i] + v[i]*h + 0.5*f[i]*h*h; // Esto quisiera ser x(t+h) - Se actualizan posiciones en un paso entero
		
		//Condición periódica de contorno para la posición
		if(x[i]>L)
		{
			x[i] = x[i]-L;
		}
		else if(x[i]<0)
		{
			x[i] = x[i]+L;
		}
		
		v_mediopaso[i] = v[i] + 0.5*f[i]*h; // Esto quisiera ser v(t+h/2). - Se actualiza en medio paso la velocidad
	}
	
	// Con las nuevas posiciones se calculan las nuevas fuerzas
	V = forces(dx_vector, F_mod, f, x, L, N); // Esto define f(t+h)
	

	// Con las nuevas fuerzas calculo el medio paso que faltaba para terminar de actualizar las velocidades
	for(i = 0; i<3*N; i++)
	{
		v[i] = v_mediopaso[i] + 0.5*f[i]*h; // Esto quisiera ser v(t+h)
	}
	
	free(v_mediopaso);
	
	return V;
}

double velocity_verlet_con_P(double* x, double* v, double* dx_vector, double* f, double* F_mod, double* P, double h, double L, int N)
{
	// f es el vector que genera forces afuera de esta funcion y que le damos como dato
	int i;
	double V;
	double *v_mediopaso = (double *) malloc(3*N*sizeof(double)); 
	
	for(i = 0; i < 3*N; i++)
	{
		v_mediopaso[i] = 0.0;
	}

	for(i = 0; i<3*N; i++)
	{
		x[i] = x[i] + v[i]*h + 0.5*f[i]*h*h; // Esto quisiera ser x(t+h) - Se actualizan posiciones en un paso entero
		
		//Condición periódica de contorno para la posición
		if(x[i]>L)
		{
			x[i] = x[i]-L;
		}
		else if(x[i]<0)
		{
			x[i] = x[i]+L;
		}
		
		v_mediopaso[i] = v[i] + 0.5*f[i]*h; // Esto quisiera ser v(t+h/2). - Se actualiza en medio paso la velocidad
	}
	
	// Con las nuevas posiciones se calculan las nuevas fuerzas
	
	V = forces_con_presion(dx_vector, F_mod, f, x, P,  L, N);

	// Con las nuevas fuerzas calculo el medio paso que faltaba para terminar de actualizar las velocidades
	for(i = 0; i<3*N; i++)
	{
		v[i] = v_mediopaso[i] + 0.5*f[i]*h; // Esto quisiera ser v(t+h)
	}
	
	free(v_mediopaso);
	
	return V;
}

double Verlet_coef(double* x, double L, int N)
{
	double C = 0;
	double lambda, dL, n;
	int i;
	
	n = cbrt(N);
	dL = L/n;

	for(i = 0; i<3*N; i++)
	{
		C += cos(2*M_PI*(x[i]-dL*0.5)/dL); // Es como calcular todo de una
	}
	
	lambda = C/(3.0*N);
	
	return lambda;
	
}

double MB(double* v, double T, int i)
{
	double exponente = -v[i]*v[i]/(2*T);
	double denominador = pow(2*M_PI*T, 3/2);
	return exp(exponente)/denominador;
}


double h_Boltzmann(double* v, double* y, double T, double h, int N, int m)
{
	int i;
	double H = 0.0, Delta_v, a, b;
	
	// Corro histograma para obtener el Delta_v que necesitamos 
	// Para eso busco primero los inputs que tengo que darle 
	
	// OJO: ESTO COMO SE QUE LO VAMOS A USAR CON V, YA PUSE DE SIZE 3*N, PARA OTRO VECTOR O HACERLO MAS GENERAL HAY QUE CAMBIAR ESO
	a = find_min(v,3*N); // limite del histograma
	b = find_max(v,3*N); // limite del histograma
	
	Delta_v = histograma(y,v,3*N,a,b,m);
	
	for(i = 0; i < 3*N; i++)
	{
		H += MB(v, T, i)*log(MB(v, T, i))*Delta_v;
	}
	return H/3;
}

double Reescalar(double* v, double T, double Td, int N)
{
	int i;
	double a = sqrt(Td/T);
	
	for(i = 0; i < 3*N; i++)
	{
		v[i] = a*v[i];
	}
	return 0;
}

double Presion(double Pex, double Ecin, double Vol)
{
  return (1/(3*Vol))*(Pex+2*Ecin); // La presion de exceso + la P ideal
}
