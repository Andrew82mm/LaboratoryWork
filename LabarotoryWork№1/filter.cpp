#include "filter.h"
#include <cmath>

void applyGauss(RGBQUAD **rgbInfo, unsigned int width, unsigned int height) {
    const int kernelSize = 3;
    const float kernel[kernelSize][kernelSize] = {
        { 1.0f, 4.0f, 1.0f },
        { 4.0f, 16.0f, 4.0f },
        { 1.0f, 4.0f, 1.0f }
    };
    const float factor = 1.0f / 36.0f; 
    const float increaseFactor = 1.0f;
    float normalizedKernel[kernelSize][kernelSize];
    for (int y = 0; y < kernelSize; ++y) {
        for (int x = 0; x < kernelSize; ++x) {
            normalizedKernel[y][x] = kernel[y][x] * factor * increaseFactor;
        }
    }

    RGBQUAD **temp = new RGBQUAD*[height];
    for (unsigned int i = 0; i < height; ++i) {
        temp[i] = new RGBQUAD[width];
    }

    for (unsigned int y = 1; y < height - 1; ++y) {
        for (unsigned int x = 1; x < width - 1; ++x) {
            float red = 0, green = 0, blue = 0;

            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    RGBQUAD &pixel = rgbInfo[y + ky][x + kx];
                    red += pixel.rgbRed * normalizedKernel[ky + 1][kx + 1];
                    green += pixel.rgbGreen * normalizedKernel[ky + 1][kx + 1];
                    blue += pixel.rgbBlue * normalizedKernel[ky + 1][kx + 1];
                }
            }

            temp[y][x].rgbRed = static_cast<uint8_t>(std::min(255.0f, std::max(0.0f, red)));
            temp[y][x].rgbGreen = static_cast<uint8_t>(std::min(255.0f, std::max(0.0f, green)));
            temp[y][x].rgbBlue = static_cast<uint8_t>(std::min(255.0f, std::max(0.0f, blue)));
        }
    }

    for (unsigned int i = 0; i < height; ++i) {
        delete[] rgbInfo[i];
        rgbInfo[i] = temp[i];
    }
    delete[] temp;
}

