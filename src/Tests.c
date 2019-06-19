#include "general.h"
#include "interaccion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

double TEST_pair_force()
{
	FILE* fp;
	char filename2[64];
	double V = 0.0, r_2 = 0.0, k = 0.0;
	double *F_mod = (double *) malloc(sizeof(double)); //puntero con el módulo de la fuerza, se va reescribiendo all the time

	F_mod[0] = 0.0;

	sprintf(filename2, "R2_FUERZA_V.txt");
	fp = fopen(filename2, "w");

	for(k = 0; k < 7; k = k+0.01)
	{
		r_2 = (float) (k+1);
		V = pair_force(r_2,F_mod);
		fprintf(fp,"%lf\t",r_2);
		fprintf(fp,"%lf\t",F_mod[0]);
		fprintf(fp,"%lf\n",V);
		F_mod[0] = 0.0; // lo restarteo cada vez
		printf("va por la iteracion %lf\n",k);
	}
	fclose(fp);
	return 0;
}

double TEST_forces() // hace el test para dos particulas en y=z=0.
{	
	FILE* fp;
	char filename[64];
	int i;
	
	sprintf(filename, "FORCES_TEST.txt");
	fp = fopen(filename, "w ");
	
	int N = 2;
	float L = 10;
	double *x = (double *) malloc(3*N*sizeof(double));
	double *f = (double *) malloc(3*N*sizeof(double));
	double *dx_vector = (double *) malloc(3*sizeof(double));
	double *F_mod = (double *) malloc(sizeof(double)); //puntero con el módulo de la fuerza, se va reescribiendo all the time
	
	for(i = 0; i < 3*N; i++)
	{
		x[i] = 0.0;
		f[i] = 0.0;
	}

	for(i = 0; i < 3; i++)
	{
		dx_vector[i] = 0;
	}
	F_mod[0] = 0.0;
	
	
	//quiero setear solo 2 partículas con dos posiciones iniciales fijas y sin velocidades
	x[3]=0.9*L;
	
	forces(dx_vector, F_mod, f, x, N, L);
		
	for(i = 0; i < 3*N; i = i+3)
	{	
		fprintf(fp, "%lf\t%lf\t%lf\n", f[i],f[i+1],f[i+2]);
	}
	
	fclose(fp);
	return 0;
}