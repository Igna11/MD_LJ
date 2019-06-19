#include <stdio.h>

double TEST_pair_force(double r2, double* F_mod)
{
	FILE* fp;
	char filename2[64];
	double V = 0.0, r_2 = 0.0, k = 0.0;

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

double TEST_forces(double* dx_vector, double* F_mod, double* f, double* x, int N, double L)
{	
	FILE* fp;
	char filename[64];
	int i, j, k;
	
	sprintf(filename, "FORCES_TEST.txt");
	fp = fopen(filename, "w ")
	
	//quiero setear solo 2 partículas con dos posiciones iniciales fijas y sin velocidades
	
	x[0] = 0.1*L; //eje x, en el 10% de L
	x[3] = 0.9*L; //eje x, en el 90% de L
	x[1] = x[2] = x[4] = x[5] = 0.5; //eje y, z, ambas partículas alineadas en la mitad de L
	
	forces(dx_vector, F_mod, f, x, N, L);
	for(i = 0; i < N - 1; i++)
	{
		fprintf("%i\t", i);
		for(j = i + 1; N; j++)
		{
			for(k = 0; k < 3; k++)
			{
				fprintf("%lf\n", f[3*i+k]);
			}
		}
	}
	return 0;
}