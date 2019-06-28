/* gcc -Wall -O3 -o Tests.exe main_tests.c interaccion.c general.c Tests.c -lm*/

#include "general.h"
#include "interaccion.h"
#include "Tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	// TEST_delta_x();
	// TEST_pair_force();
	// TEST_forces();
	// TEST_find_minimum();
	TEST_histograma();
	return 0;
	}