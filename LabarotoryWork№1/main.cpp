#include "bmp_reader.h"
#include "rotation.h"
#include "filters.h"
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "You should write: " << argv[0] << " file_name.bmp" << std::endl;
        return 0;
    }

    const char* fileName = argv[1];
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER fileInfoHeader;
    RGBQUAD **rgbInfo = nullptr;

// 1. Download the BMP file for initial use
    if (!readBMP(fileName, fileHeader, fileInfoHeader, rgbInfo)) {
        return 0;
    }

// 2. Rotate 90 degrees clockwise, save and free memory
    {
        RGBQUAD **rotatedClockwise = rotate90Clockwise(rgbInfo, fileInfoHeader.biWidth, fileInfoHeader.biHeight);
        std::swap(fileInfoHeader.biWidth, fileInfoHeader.biHeight);
        if (!writeBMP("rotated_90_clockwise.bmp", fileHeader, fileInfoHeader, rotatedClockwise)) {
            std::cerr << "Failed to save rotated_90_clockwise.bmp" << std::endl;
        }
        cleanupinf(rotatedClockwise, fileInfoHeader.biHeight);
        std::swap(fileInfoHeader.biWidth, fileInfoHeader.biHeight); // Restore original dimensions
    }

// 3. Reload the BMP file for the next conversion
    cleanupinf(rgbInfo, fileInfoHeader.biHeight);
    if (!readBMP(fileName, fileHeader, fileInfoHeader, rgbInfo)) {
        return 0;
    }

// 4. Rotate 90 degrees counterclockwise, save and free memory
    {
        RGBQUAD **rotatedCounterClockwise = rotate90CounterClockwise(rgbInfo, fileInfoHeader.biWidth, fileInfoHeader.biHeight);
        std::swap(fileInfoHeader.biWidth, fileInfoHeader.biHeight);
        if (!writeBMP("rotated_90_counterclockwise.bmp", fileHeader, fileInfoHeader, rotatedCounterClockwise)) {
            std::cerr << "Failed to save rotated_90_counterclockwise.bmp" << std::endl;
        }
        cleanupinf(rotatedCounterClockwise, fileInfoHeader.biHeight);
        std::swap(fileInfoHeader.biWidth, fileInfoHeader.biHeight); // Restore original dimensions
    }

// 5. Reload the BMP file to apply the Gaussian filter
    cleanupinf(rgbInfo, fileInfoHeader.biHeight);  
    if (!readBMP(fileName, fileHeader, fileInfoHeader, rgbInfo)) {
        return 0;
    }

// 6. Apply Gaussian filter and save the result
    applyGaussianFilter(rgbInfo, fileInfoHeader.biWidth, fileInfoHeader.biHeight);
    if (!writeBMP("gaussian_filtered.bmp", fileHeader, fileInfoHeader, rgbInfo)) {
        std::cerr << "Failed to save gaussian_filtered.bmp" << std::endl;
    }
    cleanupinf(rgbInfo, fileInfoHeader.biHeight);

    return 0;
}
