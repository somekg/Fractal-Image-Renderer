/**
 * @file Mandelbrot.h
 * @brief Handles the mathematical logic behind the mandelbrot fractal.
 * @author Alex
 */

#pragma once

/**
 * @class Mandelbrot
 * @brief Provides mathematical calculations for generating the Mandelbrot set.
 */
class Mandelbrot {
public:
	/** Maximum number of iteration steps to determine set membership. */
	static const int MAX_ITERATIONS = 1000;

public:

	/**
	 * @brief Construct a new Mandelbrot object.
	 */
	Mandelbrot();

	/**
	 * @brief Destroy the Mandelbrot object and release allocated resources.
	 */
	virtual ~Mandelbrot();

	/**
     * @brief Calculates the iteration count for a coordinate in the complex plane.
     * @param x The real component of the coordinate.
     * @param y The imaginary component of the coordinate.
     * @return The number of iterations before escape, determining color mapping.
     */
	static double getIterations(double x, double y);
};

