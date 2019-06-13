#include "general.h"
#include "inicializar.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

float set_x(float *x, int N, float L)
{
	int n = cbrt(N);
	int i;
	float ix,iy,iz,dL;
	
	dL = L/n;
	
	i = 0;
		
	for(ix=0; ix<n; ix++)
	{
		for(iy=0; iy<n; iy++)
		{
			for(iz=0; iz<n; iz++)
			{
				x[3*i] = dL*(ix+0.5);
				x[3*i+1] = dL*(iy+0.5);
				x[3*i+2] = dL*(iz+0.5);
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
			VCM[k] += v[3*i+k]/N;
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