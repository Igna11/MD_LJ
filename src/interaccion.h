#ifndef INTERACCION_H
#define INTERACCION_H

#include "math.h"

double pair_force(double r2, double* F_mod);
double forces(double* dx_vector, double* F_mod, int N);

#endif
