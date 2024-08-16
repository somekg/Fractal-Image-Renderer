#pragma once

#include <iostream>
#include <string>
#include <cstdint>
#include <memory>
#include <math.h>
#include <vector>
#include "Mandelbrot.h"
#include "Bitmap.h"
#include "Zoom.h"
#include "ZoomList.h"
#include "RGB.h"

using namespace std;
namespace me {
class FractalCreator
{
private:
	int m_width;
	int m_height;
	unique_ptr<int[]> m_histogram;
	unique_ptr<int[]> m_fractal;
	Bitmap m_bitmap;
	ZoomList m_zoomList;
	int m_total{ 0 };

	vector<int> m_ranges;
	vector<RGB> m_colors;
	vector<int> m_rangeTotals;

	bool m_bGotFirstRange{ false };
private:

	
	void calculateIteration();
	void calculateTotalIterations();
	void calculateRangeTotals();
	void drawFractal();

	void writeBitmap(string name);
	
public:int getRange(int iterations) const;

public:
	FractalCreator(int width, int height);
	virtual ~FractalCreator();
	void addRange(double rangeEnd, const RGB& rgb);
	void run(string name);
	void addZoom(const Zoom& zoom);
};
}


