/* Sergienko Andrey b82 group st135882@student.spbu.ru */ 
#ifndef READ_H
#define READ_H

#include "main.h"
#include <fstream>

bool readBMP(const char *fileName, BITMAPFILEHEADER &fileHeader, BITMAPINFOHEADER &fileInfoHeader, RGBQUAD **&rgbInfo);
void cleanupRGBInfo(RGBQUAD **&rgbInfo, unsigned int height);

#endif
