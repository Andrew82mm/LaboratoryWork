/* Sergienko Andrey b82 group st135882@student.spbu.ru */
#ifndef WRITE_H
#define WRITE_H

#include "main.h"
#include <fstream>

bool writeBMP(const char *fileName, const BITMAPFILEHEADER &fileHeader, const BITMAPINFOHEADER &fileInfoHeader, RGBQUAD **rgbInfo);

#endif
