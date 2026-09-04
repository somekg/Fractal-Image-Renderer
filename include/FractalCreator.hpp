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

#include "Bitmap.hpp"
#include "Mandelbrot.hpp"
#include "Zoom.hpp"
#include "ZoomList.hpp"

using namespace std;

/**
 * @class FractalCreator
 * @brief Manages the creation of the renderization of the MandelBrot image.
 */
class FractalCreator
{
private:
	int m_width, m_height;
	int m_total{0};
	int m_palette{0};
    bool m_useSSAA{true}; 

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
	 * @brief Sets color palette preset for the Cosine Palette.
	 * @param palette Palette between 0-3.
	 */ 
	void setPalette(int palette) { m_palette = palette; }

	/**
	 * @brief Toggles SSAA on/off. 
	 * @param use true to toggle SSAA on, false for off. 
	 */ 
	void setSSAA(bool use) { m_useSSAA = use; } 

	/**
	 * @brief Render the fractal image.
	 * @return Measured duration of renderization process (compression excluded).
	 */ 
	double render(); 

	/**
	 * @brief Saves png image to memory
	 * @param name File name.
	 */ 
	void saveImage(string name);

	/**
	 * @brief Adds zoom to zoom list.
	 * @details The ith zoom zooms over the fractal image created by the i-1th
	 * zoom.
	 * @param zoom Zoom object to add.
	 */ 
	void addZoom(const Zoom& zoom);

	/**
	 * @brief Goes back to last zoom frame.
	 * @details Delegates job to ZoomList.unZoom()
	 */ 
	void unZoom();

	/**
	 * @brief Returns Bitmap raw pixel information.
	 * @return Pointer to raw pixel information array.
	 */ 
	uint8_t* getPixels() { return m_bitmap.getPixels(); }

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

