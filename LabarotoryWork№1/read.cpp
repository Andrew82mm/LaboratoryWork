#include "read.h"
#include <iostream>

bool readBMP(const char *fileName, BITMAPFILEHEADER &fileHeader, BITMAPINFOHEADER &fileInfoHeader, RGBQUAD **&rgbInfo) {
    std::ifstream fileStream(fileName, std::ios::binary);
    if (!fileStream) {
        std::cerr << "Error opening file '" << fileName << "'." << std::endl;
        return false;
    }

    fileStream.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    if (fileHeader.bfType != 0x4D42) {
        std::cerr << "Error: '" << fileName << "' is not a BMP file." << std::endl;
        return false;
    }

    fileStream.read(reinterpret_cast<char*>(&fileInfoHeader), sizeof(fileInfoHeader));

    int width = fileInfoHeader.biWidth;
    int height = abs(fileInfoHeader.biHeight);
    int padding = (4 - (width * 3) % 4) % 4;

    rgbInfo = new RGBQUAD*[height];
    for (int i = 0; i < height; ++i) {
        rgbInfo[i] = new RGBQUAD[width];
    }

    fileStream.seekg(fileHeader.bfOffBits, std::ios::beg);

    for (int i = height - 1; i >= 0; --i) {
        for (int j = 0; j < width; ++j) {
            fileStream.read(reinterpret_cast<char*>(&rgbInfo[i][j]), 3);
            rgbInfo[i][j].rgbReserved = 0;
        }
        fileStream.ignore(padding);
    }

    return true;
}

void cleanupRGBInfo(RGBQUAD **&rgbInfo, unsigned int height) {
    for (unsigned int i = 0; i < height; ++i) {
        delete[] rgbInfo[i];
    }
    delete[] rgbInfo;
    rgbInfo = nullptr;
}
