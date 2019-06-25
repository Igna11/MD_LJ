#ifndef AVANZAR_H
#define AVANZAR_H

#include "math.h"

// Declaracion de funciones

double velocity_verlet(double* x, double* v, double* dx_vector, double* f, double* F_mod, double h, double L, int N);
double Verlet_coef(double* x, double L, int N);

#endif
