#include "filter.h"
#include <cmath>

Filter::Filter(int kernelSize, double sigma) {
    GenerateGaussianKernel(kernelSize, sigma);
}

void Filter::GenerateGaussianKernel(int size, double sigma) {
    const double PI = 3.14159265;
    gaussianKernel.resize(size, std::vector<double>(size));
    double sum = 0.0;

    int halfSize = size / 2;
    for (int y = -halfSize; y <= halfSize; ++y) {
        for (int x = -halfSize; x <= halfSize; ++x) {
            double value = (1 / (2 * PI * sigma * sigma)) *
                           exp(-(x * x + y * y) / (2 * sigma * sigma));
            gaussianKernel[y + halfSize][x + halfSize] = value;
            sum += value;
        }
    }

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            gaussianKernel[y][x] /= sum;
        }
    }
}

std::unique_ptr<BMP_File> Filter::ApplyGaussianFilter(const BMP_File& bmp_file, const Filter& filter) {
    int width = bmp_file.dib_header.width;
    int height = bmp_file.dib_header.height;

    auto new_bmp_file = std::make_unique<BMP_File>();
    new_bmp_file->bmp_header = bmp_file.bmp_header;
    new_bmp_file->dib_header = bmp_file.dib_header;
    new_bmp_file->file_data = new RGB[width * height];

    int halfSize = filter.gaussianKernel.size() / 2;

    for (int y = halfSize; y < height - halfSize; ++y) {
        for (int x = halfSize; x < width - halfSize; ++x) {
            double red = 0.0, green = 0.0, blue = 0.0;

            for (int ky = -halfSize; ky <= halfSize; ++ky) {
                for (int kx = -halfSize; kx <= halfSize; ++kx) {
                    RGB pixel = bmp_file.file_data[(y + ky) * width + (x + kx)];
                    double weight = filter.gaussianKernel[ky + halfSize][kx + halfSize];
                    blue += pixel.blue * weight;
                    green += pixel.green * weight;
                    red += pixel.red * weight;
                }
            }

            new_bmp_file->file_data[y * width + x] = RGB(
                static_cast<uint8_t>(std::min(std::max(red, 0.0), 255.0)),
                static_cast<uint8_t>(std::min(std::max(green, 0.0), 255.0)),
                static_cast<uint8_t>(std::min(std::max(blue, 0.0), 255.0))
            );
        }
    }

    return new_bmp_file;
}

std::unique_ptr<BMP_File> Filter::FlipBMP90Clockwise(const BMP_File& bmp_file) {
    auto new_bmp_file = std::make_unique<BMP_File>();

    new_bmp_file->bmp_header = bmp_file.bmp_header;
    new_bmp_file->dib_header = bmp_file.dib_header;

    std::swap(new_bmp_file->dib_header.width, new_bmp_file->dib_header.height);

    new_bmp_file->file_data = new RGB[new_bmp_file->dib_header.width * new_bmp_file->dib_header.height];

    for (uint32_t y = 0; y < bmp_file.dib_header.height; ++y) {
        for (uint32_t x = 0; x < bmp_file.dib_header.width; ++x) {
            uint32_t old_index = y * bmp_file.dib_header.width + x;
            uint32_t new_index = x * new_bmp_file->dib_header.width + (bmp_file.dib_header.height - 1 - y);
            new_bmp_file->file_data[new_index] = bmp_file.file_data[old_index];
        }
    }

    return new_bmp_file;
}

std::unique_ptr<BMP_File> Filter::FlipBMP90CounterClockwise(const BMP_File& bmp_file) {
    auto new_bmp_file = std::make_unique<BMP_File>();

    new_bmp_file->bmp_header = bmp_file.bmp_header;
    new_bmp_file->dib_header = bmp_file.dib_header;

    std::swap(new_bmp_file->dib_header.width, new_bmp_file->dib_header.height);

    new_bmp_file->file_data = new RGB[new_bmp_file->dib_header.width * new_bmp_file->dib_header.height];

    for (uint32_t y = 0; y < bmp_file.dib_header.height; ++y) {
        for (uint32_t x = 0; x < bmp_file.dib_header.width; ++x) {
            uint32_t old_index = y * bmp_file.dib_header.width + x;
            uint32_t new_index = (bmp_file.dib_header.width - 1 - x) * new_bmp_file->dib_header.width + y;
            new_bmp_file->file_data[new_index] = bmp_file.file_data[old_index];
        }
    }

    return new_bmp_file;
}

