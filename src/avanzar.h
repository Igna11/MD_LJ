#ifndef AVANZAR_H
#define AVANZAR_H

#include "math.h"

// Declaracion de funciones

double velocity_verlet(double* x, double* v, double* dx_vector, double* f, double* F_mod, double h, double L, int N);
double Verlet_coef(double* x, double L, int N);
double MB(double* v, double T, int i);
double h_Boltzmann(double* v, double* y, double T, double h, int N);

#endif
