/*
    Andrew Sergienko st135882@student.spbu.ru
*/
#ifndef FILTERS_H
#define FILTERS_H

#include "bmp_reader.h"
#include <memory>

// Apply Gaussian filter
void ApplyGaussianFilter(BMP_File* bmp_file, int size, double sigma);

// Function to flip BMP image 90 degrees clockwise
std::unique_ptr<BMP_File> FlipBMP90Clockwise(const BMP_File& bmp_file);

// Function to flip BMP image 90 degrees counter-clockwise
std::unique_ptr<BMP_File> FlipBMP90CounterClockwise(const BMP_File& bmp_file);

#endif

