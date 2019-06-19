#ifndef TESTS_H
#define TESTS_H

#include <stdio.h>
#include "math.h"

//declaracion de funciones

double TEST_pair_force(double r2, double* F_mod);
double TEST_forces(double* dx_vector, double* F_mod, double* f, double* x, int N, double L);

#endif
