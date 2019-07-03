#ifndef AVANZAR_H
#define AVANZAR_H

#include "math.h"

double velocity_Verlet(double *x,double *v, double *f, int N, double h, double L);
double inicializar(double *x, double *v,double *f, int N, double L, double T);
#endif
