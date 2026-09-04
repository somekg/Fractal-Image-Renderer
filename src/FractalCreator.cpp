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

double FractalCreator::render() {
    auto start = chrono::high_resolution_clock::now();

    drawFractal(); 

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    return elapsed.count(); 
}

void FractalCreator::saveImage(string name) {
    writeBitmap(name); // Only happens when the user presses 'S'
}

void FractalCreator::drawFractal() {
    double A[3] = {0.5, 0.5, 0.5};      
    double B[3] = {0.5, 0.5, 0.5};      
    double C[3] = {1.0, 1.0, 1.0};      
    double D[3] = {0.0, 0.0, 0.0}; 

    // Procedural Cosine Palettes
    switch (m_palette % 4) {
        case 0: // Deep Blue 
            D[0] = 0.0; D[1] = 0.10; D[2] = 0.20; break;
        case 1: // Fiery Sunset (Orange/Red/Yellow)
            D[0] = 0.0; D[1] = 0.33; D[2] = 0.67; break;
        case 2: // Blood Red & Void Black (Replaced the green one!)
            A[0] = 0.5; A[1] = 0.0; A[2] = 0.0; 
            B[0] = 0.5; B[1] = 0.0; B[2] = 0.0; 
            C[0] = 1.0; C[1] = 1.0; C[2] = 1.0; 
            D[0] = 0.0; D[1] = 0.0; D[2] = 0.0; 
            break;
        case 3: // Neon Synthwave (Pink/Cyan)
            C[0] = 1.0; C[1] = 1.0; C[2] = 1.0;
            D[0] = 0.5; D[1] = 0.20; D[2] = 0.25; break;
    }   

    // 2x2 Sub-pixel offsets (0.25 and 0.75)
    double offsets[2] = {0.25, 0.75};

    #pragma omp parallel for schedule(dynamic)
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            
            double total_t = 0.0;
            int valid_samples = 0;

            // Determine how many samples to take
            int samples = m_useSSAA ? 2 : 1;
            double no_ssaa_offset[1] = {0.5}; // Center of pixel

            for (int sy = 0; sy < samples; sy++) {
                for (int sx = 0; sx < samples; sx++) {
                    
                    double x_off = m_useSSAA ? offsets[sx] : no_ssaa_offset[sx];
                    double y_off = m_useSSAA ? offsets[sy] : no_ssaa_offset[sy];

                    pair<double, double> coords = 
                        m_zoomList.doZoom(x + x_off, y + y_off);
                    
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

void FractalCreator::unZoom() {
    m_zoomList.unZoom();
}

void FractalCreator::writeBitmap(string name) {
	m_bitmap.write(name);
}