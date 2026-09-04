/**
 * @file FractalCreator.h
 * @brief Implementation of the FractalCreator class.
 * @author Alex
 */

#pragma once

#include <chrono>
#include <cstdint>
#include <iostream>
#include <math.h>
#include <memory>
#include <string>
#include <vector>

#include "Bitmap.h"
#include "Mandelbrot.h"
#include "Zoom.h"
#include "ZoomList.h"

using namespace std;

/**
 * @class FractalCreator
 * @brief Manages the creation of the renderization of the MandelBrot image.
 */
class FractalCreator
{
private:
	int m_width, m_height;
	int m_total{ 0 };

	Bitmap m_bitmap;
	ZoomList m_zoomList;

public:
	/**
	 * @brief Construct a new FractalCreator object with specified dimensions.
	 * @param width The width of the output image in pixels.
	 * @param height The height of the output image in pixels.
	 */
	FractalCreator(int width, int height);

	/**
	 * @brief Destroy the FractalCreator object and release allocated resources.
	 */
	virtual ~FractalCreator();

	/**
	 * @brief Initilize fractal image creation process.
	 * @param name Name of the image output.
	 * @return Measured duration of renderization process (compression excluded).
	 */ 
	int run(string name);

	/**
	 * @brief Adds zoom to zoom list.
	 * @details The ith zoom zooms over the fractal image created by the i-1th
	 * zoom.
	 * @param zoom Zoom object to add.
	 */ 
	void addZoom(const Zoom& zoom);

private:

	/**
	 * @brief Renders the fractal image.
	 */
	void drawFractal();
	
	/**
	 * @brief Writes the image to memory
	 * @details Delegates responsibility to Bitmap.write(string filename).
	 */ 
	void writeBitmap(string name);
};

