#include <fstream>
#include <iostream>

#include "Bitmap.h"
#include "Bitmap_InfoHeader.h"
#include "Bitmap_FileHeader.h"

using namespace me;
using namespace std;

namespace me {

	Bitmap::Bitmap(int width, int height): m_width(width), m_height(height), m_pPixels(new uint8_t[width*height*3]{}) {

	}

	void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
		uint8_t* pPixel = m_pPixels.get(); 

		pPixel += (y *3) * m_width + (x*3);

		pPixel[0] = blue;
		pPixel[1] = green;
		pPixel[2] = red;

	}

	bool Bitmap::write(string filename) {
		BitmapFileHeader fileHeader;
		BitmapInfoHeader infoHeader;

		fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + m_width * m_height * 3;
		fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

		infoHeader.width = m_width;
		infoHeader.height = m_height;

		ofstream file;

		file.open(filename, ios::out | ios::binary);

		if (!file) {
			std::cout << "Failed to open file" << endl;
			return false;
		}
		
		file.write((char*)&fileHeader, sizeof(fileHeader));
		file.write((char*)&infoHeader, sizeof(infoHeader));
		file.write((char*)m_pPixels.get(), m_width * m_height * 3);

		file.close();

		if (!file) {
			std::cout << "Failed to close file" << endl;
			return false;
		}

		return true;
	}

	Bitmap::~Bitmap() {

	}






}