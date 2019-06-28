#ifndef GENERAL_H
#define GENERAL_H
#include "math.h"

double random();
double gaussiana(double,double);
double norma2(double*);
double delta_x(double*, double*, double*, double);
double histograma(double *y,double *x,int n,double a,double b,int m);
double find_min(double* array, int size);
double find_max(double* array, int size);

#endif