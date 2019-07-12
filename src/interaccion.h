#ifndef INTERACCION_H
#define INTERACCION_H

#include "math.h"

double pair_force(double* F_mod, double r2);
double forces(double* dx_vector, double* F_mod, double* f, double* x, double L, int N);
double forces_con_presion(double* dx_vector, double* F_mod, double* f, double* x, double* P, double L, int N);
double Presion(double Pex, double Ecin, double Vol);

#endif
