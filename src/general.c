#include "general.h"
#include "stdlib.h"
double random()
{
	return ((double)rand()) / ((double) RAND_MAX);
}

double gaussiana(double mu, double sigma)
{
	int i;
	int n = 10;
	double z = 0;
	
	for(i = 0; i<n; i++)
	{
		z += random();
	}
	z = sqrt(12*(double)n)*(z/(double)n - 0.5);
	return z*sigma+mu;
}

double norma2(double* V)
{
	int i;
	double norma = 0;
	for(i = 0; i<3; i++)
	{
		norma += V[i]*V[i];
	}
	return norma;
}

double delta_x(double* x1, double* x2, double* dx, double L)
{
	/* 
	Esta función va a devolver en el vector dx (que le estamos dando para que _rellene_ la diferencia componente a componente entre los vectores x1 y x2.
	Incluir las condiciones acorde a L da la condicion periodica de borde.
	*/
	//Condicion periodica de contorno en los bordes
	int k;
	for(k = 0; k < 3; k++)
	{
		dx[k] = x1[k] - x2[k];
		if(dx[k] < -L/2)
		{
			dx[k] = dx[k] + L;
		}
		else if(dx[k] > L/2)
		{
			dx[k] = dx[k] - L;
		}
	}
	return 0;
}

double histograma(double *y,double *x,int n,double a,double b,int m)
{

	/* 
	 Histograma del vector de datos x[0]...x[n-1] 
	 
	 m  = cantidad de columnas del histograma
	 a,b= limites del histograma 
	 
	 y[0]...y[m-1]  valores de las columnas (normalizados)
	 y[m]...y[2m-1] valores de las marcas de clase
	 (osea el y se lo damos basicamente para que lo rellene con los datos. hasta m-1 van a ser las alturas de las columnas y de m en adelante van a ser sus posiciones)

	*/

	int    i,j;
	double h,hh,s;

	s=1.0/(double)n;
	h=(b-a)/(double)m; // interpreto que esto es el ancho de los bins, que es lo que nos interesa en nuestro caso
	hh=h/2.0;

	for(i=0;i<m;i++)
	{
		*(y+i)=0.0;
		*(y+m+i)=(double)i*h+a+hh;
	}

	for(i=0;i<n;i++)
	{
		j=(int)floor((*(x+i)-a)/h);

		if (j<0) j=0;
		if (j>m) j=m-1;

		y[j]=y[j]+s;
	}

	return h; // entonces le pido que returnee h
	}

double find_min(double* array, int size)
{
	/* Le paso el vector y su tamaño y me encuentra el elemento minimo */
	
	double minimum;
	int c;
	minimum = array[0];
   
    for (c = 1; c < size; c++)
    {
        if (*(array+c) < minimum)
        {
           minimum = *(array+c);
        }
    }
	
	return minimum;
	
}


double find_max(double* array, int size)
{
	/* Le paso el vector y su tamaño y me encuentra el elemento minimo */
	
	double maximum;
	int c;
	maximum = array[0];
   
    for (c = 1; c < size; c++)
    {
        if (*(array+c) > maximum)
        {
           maximum = *(array+c);
        }
    }
	
	return maximum;
	
}