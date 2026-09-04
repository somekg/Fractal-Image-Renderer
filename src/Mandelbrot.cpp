/**
 * @file Mandelbrot.h
 * @brief Implementation of the Mandelbrot class.
 * @author Alex
 */

#include <iostream>
#include <math.h>

#include "Mandelbrot.hpp"

using namespace std;

Mandelbrot::Mandelbrot() {}

Mandelbrot::~Mandelbrot() {}

double Mandelbrot::getIterations(double x, double y) {
	const double BAILOUT = 256.0;
	const double BAILOUT_SQUARED = BAILOUT * BAILOUT; 

	double zReal = 0;
    double zImag = 0;

	int iterations = 0;

	while (iterations < MAX_ITERATIONS) {
		// Mandelbrot fractal recursive formula.
		double zRealSq = zReal * zReal;
        double zImagSq = zImag * zImag;

		// Escape condition.
		if (zRealSq + zImagSq > BAILOUT_SQUARED) {
			// Fractional escape time calculation
            double z_abs = sqrt(zRealSq + zImagSq);
            double fraction = 1.0 - log(log(z_abs)) / log(2.0);
            return iterations + fraction;
		}
		
		zImag = 2.0 * zReal * zImag + y;
        zReal = zRealSq - zImagSq + x;

		iterations++;
	}

	return MAX_ITERATIONS;
}