/*
    Andrew Sergienko st135882@student.spbu.ru
*/
#include "filters.h"
#include <cmath>

// Function to flip BMP image 90 degrees clockwise
std::unique_ptr<BMP_File> FlipBMP90Clockwise(const BMP_File& bmp_file)
{
    auto new_bmp_file = std::make_unique<BMP_File>();

    // Copy headers
    new_bmp_file->bmp_header = bmp_file.bmp_header;
    new_bmp_file->dib_header = bmp_file.dib_header;

    // Swap width and height
    std::swap(new_bmp_file->dib_header.width, new_bmp_file->dib_header.height);

    new_bmp_file->file_data = new RGB[new_bmp_file->dib_header.width * new_bmp_file->dib_header.height];

    for (uint32_t y = 0; y < bmp_file.dib_header.height; ++y)
    {
        for (uint32_t x = 0; x < bmp_file.dib_header.width; ++x)
        {
            uint32_t old_index = y * bmp_file.dib_header.width + x;
            uint32_t new_index = x * new_bmp_file->dib_header.width + (bmp_file.dib_header.height - 1 - y);
            new_bmp_file->file_data[new_index] = bmp_file.file_data[old_index];
        }
    }

    return new_bmp_file;
}

// Function to flip BMP image 90 degrees counter-clockwise
std::unique_ptr<BMP_File> FlipBMP90CounterClockwise(const BMP_File& bmp_file)
{
    auto new_bmp_file = std::make_unique<BMP_File>();

    // Copy headers
    new_bmp_file->bmp_header = bmp_file.bmp_header;
    new_bmp_file->dib_header = bmp_file.dib_header;

    // Swap width and height
    std::swap(new_bmp_file->dib_header.width, new_bmp_file->dib_header.height);

    new_bmp_file->file_data = new RGB[new_bmp_file->dib_header.width * new_bmp_file->dib_header.height];

    for (uint32_t y = 0; y < bmp_file.dib_header.height; ++y)
    {
        for (uint32_t x = 0; x < bmp_file.dib_header.width; ++x)
        {
            uint32_t old_index = y * bmp_file.dib_header.width + x;
            uint32_t new_index = (bmp_file.dib_header.width - 1 - x) * new_bmp_file->dib_header.width + y;
            new_bmp_file->file_data[new_index] = bmp_file.file_data[old_index];
        }
    }

    return new_bmp_file;
}

// Its function for generate the kernel for Gaussian filter
void GenereteGausKernel(int size, double sigma, double** gaussianKernel)
{
    double sum = 0.0;
    const double PI = 3.14159265;

    //double gaussianKernel[length_gaus][height_gaus];
    for (int height = 0; height < size; ++height)
    {
        for (int length = 0; length < size; ++length)
        {
            gaussianKernel[height][length] = (1 / (2 * PI * sigma * sigma)) *
                                             (exp(-(height * height + length * length)) / 2 * sigma * sigma) ;

            sum += gaussianKernel[height][length]; // For stabilization Gaus karnel
        }
    }

    // Stabilization Gaus karnel
    for (int height = 0; height < size; height++)
    {
        for (int length = 0; length < size; length++)
        {
            gaussianKernel[height][length] /= sum;
        }
    }
}

// Function to apply Gaussian filter to an image
void ApplyGaussianFilter(BMP_File* bmp_file, int size, double sigma)
{
    int width = bmp_file->dib_header.width;
    int height = bmp_file->dib_header.height;

    // Create buffer to store result
    RGB* file_data = new RGB[width * height];

    // Generate Gaus kernel
    double** gaussianKernel = new double*[size];
    for (int i = 0; i < size; ++i)
    {
        gaussianKernel[i] = new double[size];
    }
    GenereteGausKernel(size, sigma, gaussianKernel);

    // Apply Gausian filter line by line
    for (int y = 1; y < height - 1; ++y)
    {
        for (int x = 1; x < width - 1; ++x)
        {
            double red = 0.0, green = 0.0, blue = 0.0;

            // Aply Gaussian kernel to a 3x3 window of pixels
            for (int ky = -1; ky <= 1; ++ky)
            {
                for (int kx = -1; kx <= 1; ++kx)
                {
                    RGB pixel = bmp_file->file_data[(y + ky) * width + (x + kx)];
                    blue += pixel.blue * gaussianKernel[ky + 1][kx + 1];
                    green += pixel.green * gaussianKernel[ky + 1][kx + 1];
                    red += pixel.red * gaussianKernel[ky + 1][kx + 1];
                }
            }

            // Write the reslt to the output buffer
            file_data[y * width + x] = RGB(
                                           static_cast<uint8_t>(std::min(std::max(red, 0.0), 255.0)),
                                           static_cast<uint8_t>(std::min(std::max(green, 0.0), 255.0)),
                                           static_cast<uint8_t>(std::min(std::max(blue, 0.0), 255.0))
                                       );
        }
    }

    // Copy the procesed data back original image
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            bmp_file->file_data[y * width + x] = file_data[y * width + x];
        }
    }

    // Free memory for the result
    delete[] file_data;
    for (int i = 0; i < size; ++i)
    {
        delete[] gaussianKernel[i];
    }
    delete[] gaussianKernel;
}
