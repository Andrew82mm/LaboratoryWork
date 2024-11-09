#ifndef BMP_READER_H
#define BMP_READER_H

#include "main.h"
#include <fstream>

bool readBMP(const char *fileName, BITMAPFILEHEADER &fileHeader, BITMAPINFOHEADER &fileInfoHeader, RGBQUAD **&rgbInfo); // Loads a BMP file and stores information in the headers and pixel array
bool writeBMP(const char *fileName, const BITMAPFILEHEADER &fileHeader, const BITMAPINFOHEADER &fileInfoHeader, RGBQUAD **rgbInfo); // Saves the pixel array and headers to a BMP file 
void cleanupinf(RGBQUAD **&inf, unsigned int height); // Clears the memory allocated for the pixel array

#endif

