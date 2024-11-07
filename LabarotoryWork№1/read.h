#ifndef READ_H
#define READ_H

#include "main.h"
#include <fstream>

bool readBMP(const char *fileName, BITMAPFILEHEADER &fileHeader, BITMAPINFOHEADER &fileInfoHeader, RGBQUAD **&rgbInfo);
void cleanupRGBInfo(RGBQUAD **&rgbInfo, unsigned int height);

#endif
