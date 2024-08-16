#pragma once

namespace me {
class Mandelbrot {
public:
	static const int MAX_ITERATIONS = 12000;
public:
	Mandelbrot();
	virtual ~Mandelbrot();


	static int getIterations(double x, double y);
};
}


