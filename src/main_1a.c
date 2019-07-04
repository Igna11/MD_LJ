/* gcc -Wall -O3 -o DM_1a.exe main_1a.c visualizacion.c interaccion.c general.c avanzar.c inicializar.c -lm*/

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

/* Definicion del main
	
 ESTE MAIN: Te va a devolver un archivo que se llama EPot_ECin_Lambda_H.txt donde la primer columna es el numero de iteracion y 
 las siguientes son como están escritas en el titulo.
 Ese archivo lo importas en "Correlacion(Tau).ipynb" y vas a poder estudiar lambda y H para ver la termalizacion
 + te va a dar la correlacion y la cantidad de iteraciones necesaria para evitar estados correlacionados.
*/
	int N, i, m;
	double L, T, rho, h, E_pot, vel,lambda, H;
	
	printf("\nPasame el numero de particulas ameo\n");
	scanf("%int", &N);
	printf("\nPasame la temperatura\n");
	scanf("%lf", &T);
	printf("\nPasame la densidad de particulas\n");
	scanf("%lf", &rho);
	
//-------------------- CALCULA EL LADO DE LA CAJA (CUBICA) EN FUNCION DE RHO---//
	
	L = cbrt((double)N/rho);
	
//-----------------------------------------------------------------------------//
	double *x = (double *) malloc(3*N*sizeof(double)); //posición de cada partícula
	double *v = (double *) malloc(3*N*sizeof(double)); //velocidad de cada partícula
	double *f = (double *) malloc(3*N*sizeof(double)); //fuerza de sobre cada partícula
	double *dx_vector = (double *) malloc(3*sizeof(double)); //vector distancia entre un par de partículas (la menor entre la distancia con la partícula real y la partícula imagen)
	double *F_mod = (double *) malloc(sizeof(double)); //puntero con el módulo de la fuerza, se va reescribiendo all the time
	double *y = (double *) malloc(2*3*N*sizeof(double)); // este es un vector auxiliar que usamos para que la funcion h_boltzman rellene. tiene que tener 2*tamaño de v. (no hace falta reiniciarlo en ppio pero lo reinicio por las dudas)
		
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
	
	for(i = 0; i < 6*N; i++)
	{
		y[i] = 0.0;
	}
	
	F_mod[0] = 0.0;

//----------------------------------------------------------------------------------------------//
// El formato del filename ".lammpstrj", ese VMD lo lee comodamente
	char filename[255];
	sprintf(filename, "prueba_nyp.lammpstrj_1a");

	FILE* fp, *fp1;
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

	fp = fopen("EPot_ECin_Lambda_H.txt","w");
	fp1 = fopen("velocidades.txt","w");
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
		
		m = 10; // cantidad de columnas en el histograma de velocidades para H_boltzmann
		H = h_Boltzmann(v, y, T, h, N,m); 
		
		fprintf(fp,"%i\t%lf\t%lf\t%lf\t%lf\n", l, (double)E_pot/(double)N, vel/(2.0*N), lambda, H);
		
		fprintf(fp1,"%i\t",l);
		for(i=0;i<3*N;i++)
		{
		  fprintf(fp1,"%lf ",v[i]);
		}
		fprintf(fp1,"\n");
		
		printf("Frame: %i\t \n",l);
		save_lammpstrj(filename, x, v, N, L, l);  // La guardo (append para 0<l)
	}
	fclose(fp);
	fclose(fp1);
	
	free(x);
	free(v);
	free(f);
	free(dx_vector);
	free(y);
	free(F_mod);
	
	
// Capaz notaron que las velocidades estan al pedo, nos va a servir guardarlas
// para tener checkpoints de estados bien termalizados.
// Checkpoint is love, checkpoint is life
//-----------------------------------------------------------------------------//

	return 0;
}