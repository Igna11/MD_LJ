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
	double L, T, rho, h, E_pot, vel,lambda;
	
	printf("\nPasame el numero de particulas ameo\n");
	scanf("%int", &N);
	printf("\nPasame la temperatura\n");
	scanf("%lf", &T);
	printf("\nPasame la densidad de particulas\n");
	scanf("%lf", &rho);
	
//-------------------- CALCULA EL LADO DE LA CAJA (CUBICA) EN FUNCION DE RHO---//
	
	L = cbrt(N/rho);
	
//-----------------------------------------------------------------------------//
	double *x = (double *) malloc(3*N*sizeof(double)); //posición de cada partícula
	double *v = (double *) malloc(3*N*sizeof(double)); //velocidad de cada partícula
	double *f = (double *) malloc(3*N*sizeof(double)); //fuerza de sobre cada partícula
	double *dx_vector = (double *) malloc(3*sizeof(double)); //vector distancia entre un par de partículas (la menor entre la distancia con la partícula real y la partícula imagen)
	double *F_mod = (double *) malloc(sizeof(double)); //puntero con el módulo de la fuerza, se va reescribiendo all the time
	
//------------------ REINICIAMOS x, v, f, dx_vector y F_mod ----------------------------------------//

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

//----------------------------------------------------------------------------------------------//
// El formato del filename ".lammpstrj", ese VMD lo lee comodamente
	char filename[255];
	sprintf(filename, "prueba_nyp.lammpstrj");

	FILE* fp;
	int N_frames;
	
	printf("\nPasame la cantidad de frames que queres\n");
	scanf("%i", &N_frames);
	printf("\nPasame el paso temporal h\n");
	scanf("%lf", &h);
	
// Configuración de posiciones, velocidades y fuerzas iniciales

	set_x(x, L, N);
	set_v(v, T, N);
	forces(dx_vector, F_mod, f, x, L, N);

// Asignacion de velocidades	

	fp = fopen("EPot_ECin_Lambda.txt","w");
	for(int l = 0; l < N_frames; l++)
	{	
		// Sumo todas las velocidades, la reinicio primero
		vel = 0.0;
		for(i = 0; i < 3*N; i++)
		{
			vel += v[i]*v[i];
		}
		
		E_pot = velocity_verlet(x, v, dx_vector, f, F_mod, h, L, N);
		
		lambda = Verlet_coef(x,L,N);
		
		fprintf(fp,"%lf\t%lf\t%lf\n", (double)E_pot/(double)N, vel/(2.0*N),lambda);
		
		printf("Frame: %i\t \n",l);
		save_lammpstrj(filename, x, v, N, L, l);  // La guardo (append para 0<l)
	}
	fclose(fp);
	
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