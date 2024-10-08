#pragma once
#pragma pack(2)
#include <cstdint>
using namespace std;

namespace me {
struct BitmapFileHeader {
	char header[2]{'B', 'M'};
	int32_t fileSize;
	int16_t reserved1{ 0 };
	int16_t reserved2{ 0 };
	int32_t dataOffset;
};
}
