/**
 * @file Bitmap.cpp
 * @brief Implements the Bitmap class.
 * @author Alex
 */

#include <iostream>

#include "Bitmap.hpp"

// Temporarily disable the missing field warning from the STB library
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#pragma GCC diagnostic pop // Turn the warnings back on for the rest of our code

using namespace std;

Bitmap::Bitmap(int width, int height): 
    m_width(width), m_height(height), 
    pixelCount(width * height * 4), 
    m_pPixels(new uint8_t[pixelCount]{}) {}

Bitmap::~Bitmap() {}

void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t* pPixel = m_pPixels.get(); 

    pPixel += (y * m_width + x) * 4; 
      
    pPixel[0] = red;
    pPixel[1] = green;
    pPixel[2] = blue;
    pPixel[3] = 255; 
}

bool Bitmap::write(string filename) {
    // Calculate the "stride" (how many bytes are in a single row of pixels)
    int stride = m_width * 4;

    int success = stbi_write_png(filename.c_str(), 
        m_width, m_height, 4, m_pPixels.get(), stride);
    
    if (!success) {
        cout << "Failed to write PNG file: " << filename << endl;
        return false;
    }
    
    return true;
}