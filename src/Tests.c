#include "general.h"
#include "interaccion.h"
#include "Tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

double TEST_delta_x()
{
	double *x1 = (double *) malloc(3*sizeof(double));
	double *x2 = (double *) malloc(3*sizeof(double));
	double *dx = (double *) malloc(3*sizeof(double));
	int L = 10;
	
	// DEFINO X1, X2 Y DX
	x1[0] = 1;
	x1[1] = x1[2] = 5;
	
	x2[0] = 3;
	x2[1] = x2[2] = 2;
	
	int k;
	for(k = 0; k < 3; k++)
	{
		dx[k] = x1[k] - x2[k];
		printf("primero vale %lf\n",dx[k]);
		if(dx[k] < -L/2)
		{
			dx[k] = dx[k] + L;
		}
		else if(dx[k] > L/2)
		{
			dx[k] = dx[k] - L;
		}
		printf("y despues de los ifs vale %lf\n",dx[k]);
	}
	
	printf("el vector queda %lf\t%lf\t%lf\n", dx[0],dx[1],dx[2]);
	
	free(x1);
	free(x2);
	free(dx);
	return 0;
}


/*
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
	
	free(F_mod);
	
	return 0;
}
*/



double TEST_forces()
{	
	/* 
	Este test fue acompañado de multiples "printf" dentro de la funcion original forces para hacer un seguimiento (luego se descartaron los printf).
	El archivo que se crea de este test "FORCES_TEST" devuelve una matriz en la que cada fila es una particula y las columnas son las componentes x,y y z de la fuerza sobre dicha particula.
	Hace el test para dos particulas: una posicionada en (0,0,0) y la otra en (0,0,2). Ambas sin velocidad.
	*/

	FILE* fp;
	char filename[64];
	int i;
	
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
	x[5]=0.2*L;
		
	forces(dx_vector, F_mod, f, x, L, N);
	
	sprintf(filename, "FORCES_TEST.txt");
	fp = fopen(filename, "w ");
		
	for(i = 0; i < 3*N; i = i+3)
	{	
		fprintf(fp, "%lf\t%lf\t%lf\n", f[i],f[i+1],f[i+2]);
	}
	
	fclose(fp);
	
	free(x);
	free(f);
	free(dx_vector);
	free(F_mod);
	
	return 0;
}

double TEST_find_minimum()
{
	int i;
	double min;
	double *array = (double *) malloc(3*sizeof(double));
	
	for(i = 0; i < 3; i++)
	{
		array[i] = i+80;
	}
	
	min = find_min(array,3); // le paso el vector y el tamaño del mismo
	printf("el minimo es %lf\n",min);
	
	return 0.0;
}