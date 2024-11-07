/* Sergienko Andrey b82 group st135882@student.spbu.ru */ 
#include "read.h"
#include "write.h"
#include "rotation.h"
#include "filter.h"
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " input_file.bmp" << std::endl;
        return 0;
    }

    const char* fileName = argv[1];
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER fileInfoHeader;
    RGBQUAD **rgbInfo = nullptr;

    if (!readBMP(fileName, fileHeader, fileInfoHeader, rgbInfo)) {
        return 0;
    }

    {
        RGBQUAD **rotatedClockwise = rotate90Clockwise(rgbInfo, fileInfoHeader.biWidth, fileInfoHeader.biHeight);
        std::swap(fileInfoHeader.biWidth, fileInfoHeader.biHeight);
        if (!writeBMP("rotated_90_clockwise.bmp", fileHeader, fileInfoHeader, rotatedClockwise)) {
            std::cerr << "Failed to save rotated_90_clockwise.bmp" << std::endl;
        }
        cleanupRGBInfo(rotatedClockwise, fileInfoHeader.biHeight);
        std::swap(fileInfoHeader.biWidth, fileInfoHeader.biHeight);
    }

    {
        RGBQUAD **rotatedCounterClockwise = rotate90CounterClockwise(rgbInfo, fileInfoHeader.biWidth, fileInfoHeader.biHeight);
        std::swap(fileInfoHeader.biWidth, fileInfoHeader.biHeight);
        if (!writeBMP("rotated_90_counterclockwise.bmp", fileHeader, fileInfoHeader, rotatedCounterClockwise)) {
            std::cerr << "Failed to save rotated_90_counterclockwise.bmp" << std::endl;
        }
        cleanupRGBInfo(rotatedCounterClockwise, fileInfoHeader.biHeight);
        std::swap(fileInfoHeader.biWidth, fileInfoHeader.biHeight);
    }

    {
        applyGauss(rgbInfo, fileInfoHeader.biWidth, fileInfoHeader.biHeight);
        if (!writeBMP("gaussian_filtered.bmp", fileHeader, fileInfoHeader, rgbInfo)) {
            std::cerr << "Failed to save gaussian_filtered.bmp" << std::endl;
        }
    }

    cleanupRGBInfo(rgbInfo, fileInfoHeader.biHeight);

    return 0;
}

