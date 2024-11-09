#include "filters.h"
#include <cmath>
#include <algorithm>

void applyGaussianFilter(RGBQUAD **inf, unsigned int width, unsigned int height) {
    const int kernelSize = 3;
    const float kernel[kernelSize][kernelSize] = 
    {
        { 1.0f, 4.0f, 1.0f },
        { 4.0f, 16.0f, 4.0f },
        { 1.0f, 4.0f, 1.0f }
    };
    const float factor = 1.0f / 36.0f;

    RGBQUAD **temp = new RGBQUAD*[height];
    for (unsigned int i = 0; i < height; ++i) {
        temp[i] = new RGBQUAD[width];
    }

    for (unsigned int y = 1; y < height - 1; ++y) {
        for (unsigned int x = 1; x < width - 1; ++x) {
            float red = 0, green = 0, blue = 0;
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    RGBQUAD &pixel = inf[y + ky][x + kx];
                    red += pixel.rgbRed * kernel[ky + 1][kx + 1];
                    green += pixel.rgbGreen * kernel[ky + 1][kx + 1];
                    blue += pixel.rgbBlue * kernel[ky + 1][kx + 1];
                }
            }
            temp[y][x].rgbRed = static_cast<uint8_t>(std::clamp(red * factor, 0.0f, 255.0f));
            temp[y][x].rgbGreen = static_cast<uint8_t>(std::clamp(green * factor, 0.0f, 255.0f));
            temp[y][x].rgbBlue = static_cast<uint8_t>(std::clamp(blue * factor, 0.0f, 255.0f));
        }
    }

    for (unsigned int i = 0; i < height; ++i) {
        delete[] inf[i];
        inf[i] = temp[i];
    }
    delete[] temp;
}

