/**
 * @file Bitmap.h
 * @brief Handles bitmap creation and png compression.
 * @author Alex
 */

#pragma once

#include <cstdint>
#include <string>
#include <memory>

using namespace std;

/**
 * @class FractalCreator
 * @brief Manages bitmap creation and png compression.
 */
class Bitmap {
private:
	int m_width{0};
	int m_height{0};
	int pixelCount{0};
	unique_ptr<uint8_t[]> m_pPixels{ nullptr };

public:

	/**
	 * @brief Construct a new Bitmap object with specified dimensions.
	 * @param width The width of the bitmap in pixels.
	 * @param height The height of the bitmap in pixels.
	 */
	Bitmap(int width, int height);

	/**
	 * @brief Destroy the Bitmap object and release allocated resources.
	 */
	virtual ~Bitmap();

	/**
	 * @brief Sets pixel color inside the bitmap.
	 * @param x X-axis coordinate of the pixel.
	 * @param y Y-axis coordinate of the pixel.
	 * @param red The red intensity value (0 to 256).
	 * @param green The green intensity value (0 to 256).
	 * @param blue The blue intensity value (0 to 256).
	 */ 
	void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
	
	uint8_t* getPixels() const { return m_pPixels.get(); }
	
	/**
	 * @brief Writes png compressed image of the bitmap into memory.
	 * @param filename Name of the saved file.
	 * @return True if writing was succesful, false otherwise.
	 */
	bool write(string filename);

};

