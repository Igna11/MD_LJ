#include "general.h"
#include "inicializar.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

float set_box(float *x; int N; float L)
{
	int n = cbrt(N);
	int i;
	float x,y,z,dL;
	
	dL = L/n;
	
	i = 0;
		
	for(x=0; x<n; x++)
	{
		for(y=0; y<n; y++)
		{
			for(z=0; z<n; z++)
			{
				x[3*i] = dL*(x+0.5);
				y[3*i+1] = dL*(y+0.5);
				z[3*i+2] = dL*(z+0.5);
				i++;
			}
		}
	}
	return dL;
}

float set_v(float *v, int N, float T)
{
	float sigma = sqrt(T);
	float VCM[3] = {0,0,0};
	int i,k;
	
	for(i = 0; i < 3*N; i++)
	{
		v[i] = gaussiana(0.0,sigma);
	}
	
	for(i=0; i < N; i++)
	{
		for(k=0;k<3; k++)
		{
			VCM[k] += V[3*i+k]/N;
		}
	}
	
	for(i=0; i < N; i++)
	{
		for(k=0;k<3; k++)
		{
			v[3*i+k] -= VCM[k];
		}
	}
	return 0.0;
}