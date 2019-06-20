/* gcc -Wall -O3 -o DM.exe main.c visualizacion.c interaccion.c general.c avanzar.c inicializar.c -lm*/

#include "general.h"
#include "interaccion.h"
#include "inicializar.h"
#include "avanzar.h"
#include "visualizacion.h"
#include "Tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	// Definicion del main
	

//------------------ MAIN DE EJEMPLO PARA VISUALIZAR CON VMD ------------------//
	int N, i;
	double L = 10, h = 0.001;
	
	printf("\nPasame el numero de particulas ameo\n");
	scanf("%int", &N);
	
	double *x = (double *) malloc(3*N*sizeof(double)); //posición de cada partícula
	double *v = (double *) malloc(3*N*sizeof(double)); //velocidad de cada partícula
	double *f = (double *) malloc(3*N*sizeof(double)); //fuerza de sobre cada partícula
	double *dx_vector = (double *) malloc(3*sizeof(double)); //vector distancia entre un par de partículas (la menor entre la distancia con la partícula real y la partícula imagen)
	double *F_mod = (double *) malloc(sizeof(double)); //puntero con el módulo de la fuerza, se va reescribiendo all the time
	
//------------------ REINICIAMOS x, v y f ----------------------------------------//
	for(i = 0; i < 3*N; i++)
	{
		x[i] = 0.0;
		v[i] = 0.0;
		f[i] = 0.0;
	}

	for(i = 0; i < 3; i++)
	{
		dx_vector[i] = 0;
	}
	F_mod[0] = 0.0;

// El formato del filename ".lammpstrj", ese VMD lo lee comodamente
	char filename[255];
	sprintf(filename, "prueba_nyp.lammpstrj");
	int N_frames;
	
	printf("\nPasame la cantidad de frames que queres\n");
	scanf("%i", &N_frames);

// Configuración de posiciones, velocidades y fuerzas iniciales

	set_x(x, N, L);
	set_v(v, N, 1);
	forces(dx_vector, F_mod, f, x, L, N);

// Asignacion de velocidades	

	for(int l = 0; l < N_frames; l++)
	{	
		for(int i = 0; i < 3*N; i = i + 3)
		{
			// x[i] = x[i] + dx*v[i]; // Genero perturbacion random 
			
			velocity_verlet(x, v, dx_vector, f, F_mod, h, L, N);
			printf("Frame: %i\t Particula %i\n",l,i);
			
			//Condición periódica de contorno para la posición
			if(x[i]>L)
			{
				x[i] = x[i]-L;
			}
			else if(x[i]<0)
			{
				x[i] = x[i]+L;
			}
		}
		save_lammpstrj(filename, x, v, N, L, l);  // La guardo (append para 0<l)
		
	}

	free(x);
	free(v);
	free(f);
	free(dx_vector);
	free(F_mod);
	
	
// Capaz notaron que las velocidades estan al pedo, nos va a servir guardarlas
// para tener checkpoints de estados bien termalizados.
// Checkpoint is love, checkpoint is life
//-----------------------------------------------------------------------------//

	return 0;
}