/* gcc -Wall -O3 -o DM_2.exe main_2.c visualizacion.c interaccion.c general.c avanzar.c inicializar.c -lm*/

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
	int N, i, Frames_x_T, It_termalizacion, It_correlacion, m, l, j = 0;

	double L, Vol, Ti, Tf, T, t, rho_i, rho_f, rho, h, E_pot, E_potN, vel, E_cinN, P_final;
	
	printf("\nPasame el numero de particulas ameo\n");
	scanf("%int", &N);
	
	printf("\nPasame la temperatura minima\n");
	scanf("%lf", &Ti);
	
	printf("\nPasame la temperatura maxima\n");
	scanf("%lf", &Tf);
	
	printf("\nPasame la densidad de particulas inicial\n");
	scanf("%lf", &rho_i);
	
	printf("\nPasame la densidad de particulas final\n");
	scanf("%lf", &rho_f);
	
	printf("\nPasame la cantidad de frames que queres por temperatura\n");
	scanf("%i", &Frames_x_T);
	
	printf("\nPasame la cantidad de iteraciones necesaria para que termalice\n");
	scanf("%i", &It_termalizacion);
	
	printf("\nPasame la cantidad de iteraciones necesaria para que descorrelacione\n");
	scanf("%i", &It_correlacion);
	
	printf("\nPasame el paso temporal h\n");
	scanf("%lf", &h);

	
//-----------------------------------------------------------------------------//
	double *x = (double *) malloc(3*N*sizeof(double)); //posición de cada partícula
	double *v = (double *) malloc(3*N*sizeof(double)); //velocidad de cada partícula
	double *f = (double *) malloc(3*N*sizeof(double)); //fuerza de sobre cada partícula
	double *dx_vector = (double *) malloc(3*sizeof(double)); //vector distancia entre un par de partículas (la menor entre la distancia con la partícula real y la partícula imagen)
	double *F_mod = (double *) malloc(sizeof(double)); //puntero con el módulo de la fuerza, se va reescribiendo all the time
	double *P = (double *) malloc(sizeof(double)); //puntero con el módulo de la presion, se va reescribiendo all the time


//----------------------------------------------------------------------------------------------//
// El formato del filename ".lammpstrj", ese VMD lo lee comodamente
	char filename[255];
	sprintf(filename, "prueba_ej2.lammpstrj");

	char filename1[255];
	char filename2[255];
	char filename3[255];
	
	// Configuración de posiciones, velocidades y fuerzas iniciales
	
	FILE* fp_pot;
	FILE* fp_cin;
	FILE* fp_p;
	
	for(rho = rho_i; rho < rho_f; rho = rho + 0.2)
	{
	//-------------------- CALCULA EL LADO DE LA CAJA (CUBICA) EN FUNCION DE RHO---//
	
		L = cbrt(N/rho);
		Vol = L*L*L;
		
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
		P[0] = 0.0;
		t = Tf;
		
		sprintf(filename1, "Epot_vs_T_rho%lf.txt", rho);
		sprintf(filename2, "Ecin_vs_T_rho%lf.txt", rho);
		sprintf(filename3, "P_vs_T_rho%lf.txt", rho);

		
		fp_pot = fopen(filename1,"w");
		fp_cin = fopen(filename2,"w");
		fp_p = fopen(filename3,"w");
		
		set_x(x, L, N);
		set_v(v, t, N);
		forces(dx_vector, F_mod, f, x, L, N);

		while(t > Ti)
		{
			fprintf(fp_pot, "%lf\t", t);
			fprintf(fp_cin, "%lf\t", t);
			fprintf(fp_p, "%lf\t", t);

			for(j = 0; j < It_termalizacion; j++)
			{
				velocity_verlet_con_P(x, v, dx_vector, f, F_mod, P, h, L, N);
			}
			
			m = 0;
			l = 0;
			while(l < Frames_x_T)
			{	
				// Sumo todas las velocidades, la reinicio primero
				vel = 0.0;
				for(i = 0; i < 3*N; i++)
				{
					vel += v[i]*v[i];
				}
				
				E_pot = velocity_verlet_con_P(x, v, dx_vector, f, F_mod, P, h, L, N);
				
				if(m >= It_correlacion)
				{					
					E_potN = (double)E_pot/(double)N;
					E_cinN = vel/(2.0*N);
					P_final = Presion(P[0], E_cinN, Vol);
					
					
					fprintf(fp_pot, "%lf ",E_potN);
					fprintf(fp_cin, "%lf ",E_cinN);
					fprintf(fp_p, "%lf ",P_final/N);
					save_lammpstrj(filename, x, v, N, L, l);  // La guardo (append para 0<l)
					
					m = 0;
					P[0] = 0.0;
					l++;
				}
				printf("T = %lf\tFrame: %i\t \n", t, l);
				//save_lammpstrj(filename, x, v, N, L, l);  // La guardo (append para 0<l)
				m++;
			}
			fprintf(fp_pot, "\n");
			fprintf(fp_cin, "\n");
			fprintf(fp_p, "\n");
			
			//calculo el T medido
			T = vel/(3.0*N);
			t -= 0.01;
			Reescalar(v, T, t, N);
		}
		fclose(fp_pot);
		fclose(fp_cin);
		fclose(fp_p);
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