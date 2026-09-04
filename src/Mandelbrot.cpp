/**
 * @file Mandelbrot.h
 * @brief Implementation of the Mandelbrot class.
 * @author Alex
 */

#include <complex>
#include <iostream>
#include <math.h>

#include "Mandelbrot.hpp"

using namespace std;

Mandelbrot::Mandelbrot() {}

Mandelbrot::~Mandelbrot() {}

double Mandelbrot::getIterations(double x, double y) {
	const int BAILOUT_RADIUS = 256;

	complex<double> z = 0;
	complex<double> c(x, y);
	
	int iterations = 0;

	while (iterations < MAX_ITERATIONS) {
		// Mandelbrot fractal recursive formula.
		z = z * z + c;

		// Escape condition.
		if (abs(z) > BAILOUT_RADIUS) {
			// Fractional escape time calculation
            double z_abs = abs(z);
            double fraction = 1.0 - log(log(z_abs)) / log(2.0);
            return iterations + fraction;
		}
		
		iterations++;
	}

	return MAX_ITERATIONS;
}