#ifndef FILTER_H
#define FILTER_H

#include "bmp_file.h"
#include <memory>
#include <vector>
#include <cmath>

class Filter {
private:
    std::vector<std::vector<double>> gaussianKernel;

    void GenerateGaussianKernel(int size, double sigma);
    
public:
    Filter(int kernelSize, double sigma);
    static std::unique_ptr<BMP_File> ApplyGaussianFilter(const BMP_File& bmp_file, const Filter& filter);
    static std::unique_ptr<BMP_File> FlipBMP90Clockwise(const BMP_File& bmp_file);
    static std::unique_ptr<BMP_File> FlipBMP90CounterClockwise(const BMP_File& bmp_file);
};

#endif

