/**
 * @file FractalCreator.cpp
 * @brief Manages the creation and rendering of fractal images.
 * @details Handles color mapping, zoom positioning and writing the final .bmp.
 * @author Alex
 */

#include <assert.h>
#include <omp.h>

#include "FractalCreator.hpp"

FractalCreator::FractalCreator(int width, int height): 
	m_width(width), m_height(height),
	m_bitmap(m_width, m_height), 
	m_zoomList(m_width, m_height) 
{
	m_zoomList.add(Zoom(m_width / 2, m_height / 2, 4.0 / m_width));
}

FractalCreator::~FractalCreator() {}

double FractalCreator::run(string name) {
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

    #pragma omp parallel for schedule(dynamic)
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            
            double total_t = 0.0;
            int valid_samples = 0;

            for (int sy = 0; sy < 2; sy++) {
                for (int sx = 0; sx < 2; sx++) {
                    
                    pair<double, double> coords = 
                        m_zoomList.doZoom(x + offsets[sx], y + offsets[sy]);
                    
                    double iter = Mandelbrot::getIterations(coords.first, coords.second);

                    if (iter != Mandelbrot::MAX_ITERATIONS) {
                        total_t += iter / 50.0; 
                        valid_samples++;
                    }
                }
            }

            uint8_t red = 0, green = 0, blue = 0;

            if (valid_samples > 0) {
                double avg_t = total_t / valid_samples;
                
                double r = A[0] + B[0] * cos(6.28318 * (C[0] * avg_t + D[0]));
                double g = A[1] + B[1] * cos(6.28318 * (C[1] * avg_t + D[1]));
                double b = A[2] + B[2] * cos(6.28318 * (C[2] * avg_t + D[2]));
                
                double edge_blend = valid_samples / 4.0;
                
                red = static_cast<uint8_t>((r * edge_blend) * 255.0);
                green = static_cast<uint8_t>((g * edge_blend) * 255.0);
                blue = static_cast<uint8_t>((b * edge_blend) * 255.0);
            }

            // Write the smoothed pixel to the bitmap
            m_bitmap.setPixel(x, y, red, green, blue);
        }
    }
}

void FractalCreator::addZoom(const Zoom& zoom) {
    m_zoomList.add(zoom);
}

void FractalCreator::writeBitmap(string name) {
	m_bitmap.write(name);
}