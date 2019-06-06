#include "general.h"
#include "stdlib.h"
float random()
{
	return ((float)rand()) / ((float) RAND_MAX);
}

float gaussiana(float mu, float sigma)
{
	int n = 10;
	float z = 0;
	
	for(int i = 0; i<n; i++)
	{
		z += random();
	}
	z = sqrt(12)*(z/n - 0.5);
	return z*sigma+mu;
}
