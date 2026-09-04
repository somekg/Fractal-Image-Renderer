/**
 * @file FractalCreator.cpp
 * @brief Manages the creation and rendering of fractal images.
 * @details Handles color mapping, zoom positioning and writing the final .bmp.
 * @author Alex
 */

#include <assert.h>

#include "FractalCreator.hpp"

FractalCreator::FractalCreator(int width, int height): 
	m_width(width), m_height(height),
	m_bitmap(m_width, m_height), 
	m_zoomList(m_width, m_height) 
{
	m_zoomList.add(Zoom(m_width / 2, m_height / 2, 4.0 / m_width));
}

FractalCreator::~FractalCreator() {}

int FractalCreator::run(string name) {
    auto render_start = chrono::high_resolution_clock::now();

	drawFractal();

	auto render_stop = chrono::high_resolution_clock::now();
	auto render_duration = 
		chrono::duration_cast<chrono::seconds>(render_stop - render_start);

	writeBitmap(name);

	return render_duration.count(); 
}

void FractalCreator::drawFractal() {
    double A[] = {0.5, 0.5, 0.5};      
    double B[] = {0.5, 0.5, 0.5};      
    double C[] = {1.0, 1.0, 1.0};      
    double D[] = {0.0, 0.10, 0.20};    

    // 2x2 Sub-pixel offsets (0.25 and 0.75)
    double offsets[2] = {0.25, 0.75};

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            
            // Accumulators for our 4 sub-pixel colors
            double total_r = 0, total_g = 0, total_b = 0;

            // 2x2 Supersampling Loop
            for (int sy = 0; sy < 2; sy++) {
                for (int sx = 0; sx < 2; sx++) {
                    
                    // Add the offsets to the base pixel coordinate
                    pair<double, double> coords = 
                    	m_zoomList.doZoom(x + offsets[sx], y + offsets[sy]);
                    double iter = 
                    	Mandelbrot::getIterations(coords.first, coords.second);

                    if (iter != Mandelbrot::MAX_ITERATIONS) {
                        double t = iter / 50.0; 
                        
                        // Add this sub-pixel's color to the running totals
                        total_r += A[0] + B[0] * cos(6.28318 * (C[0] * t + D[0]));
                        total_g += A[1] + B[1] * cos(6.28318 * (C[1] * t + D[1]));
                        total_b += A[2] + B[2] * cos(6.28318 * (C[2] * t + D[2]));
                    }
                }
            }

            // Average the totals by dividing by 4, then convert to 0-255 byte 
            // values
            uint8_t red = static_cast<uint8_t>((total_r / 4.0) * 255.0);
            uint8_t green = static_cast<uint8_t>((total_g / 4.0) * 255.0);
            uint8_t blue = static_cast<uint8_t>((total_b / 4.0) * 255.0);

            // Write the smoothed pixel to the bitmap
            m_bitmap.setPixel(x, y, red, green, blue);
        }
    }
}

void FractalCreator::writeBitmap(string name) {
	m_bitmap.write(name);
}