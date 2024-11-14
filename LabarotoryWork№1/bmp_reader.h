#ifndef BMP_READER_H
#define BMP_READER_H

#include "main.h"
#include <fstream>
// Я думаю, это должно быть не набором функций. Это должен быть класс картинки, которая умеет себя читать
// и писать, а удаление всех ресурсов должно происходить в ее деструкторе. И что же все-таки за ссылка на двойной указатель?
bool readBMP(const char *fileName, BITMAPFILEHEADER &fileHeader, BITMAPINFOHEADER &fileInfoHeader, RGBQUAD **&rgbInfo); // Loads a BMP file and stores information in the headers and pixel array
bool writeBMP(const char *fileName, const BITMAPFILEHEADER &fileHeader, const BITMAPINFOHEADER &fileInfoHeader, RGBQUAD **rgbInfo); // Saves the pixel array and headers to a BMP file
void cleanupinf(RGBQUAD **&inf, unsigned int height); // Clears the memory allocated for the pixel array

#endif

