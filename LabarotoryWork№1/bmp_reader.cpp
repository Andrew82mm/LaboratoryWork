#include "bmp_reader.h"
#include <iostream>

bool readBMP(const char *fileName, BITMAPFILEHEADER &fileHeader, BITMAPINFOHEADER &fileInfoHeader, RGBQUAD **&rgbInfo) {
    std::ifstream fileStream(fileName, std::ios::binary);
    if (!fileStream) {
        std::cerr << "Error opening file '" << fileName << "'. Attention: the file must be located in the same directory as the project files." << std::endl;
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

bool writeBMP(const char *fileName, const BITMAPFILEHEADER &fileHeader, const BITMAPINFOHEADER &fileInfoHeader, RGBQUAD **rgbInfo) {
    std::ofstream fileStream(fileName, std::ios::binary);
    if (!fileStream) {
        std::cerr << "Error creating file '" << fileName << "'." << std::endl;
        return false;
    }

    fileStream.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
    fileStream.write(reinterpret_cast<const char*>(&fileInfoHeader), sizeof(fileInfoHeader));

    int width = fileInfoHeader.biWidth;
    int height = abs(fileInfoHeader.biHeight);
    int padding = (4 - (width * 3) % 4) % 4;
    
    fileStream.seekp(fileHeader.bfOffBits, std::ios::beg);

    for (int i = height - 1; i >= 0; --i) {
        for (int j = 0; j < width; ++j) {
            fileStream.write(reinterpret_cast<const char*>(&rgbInfo[i][j]), 3);
        }
        fileStream.write("\0\0\0", padding);  //Write null bytes so that each line is a multiple of 4
    }

    return true;
}

void cleanupinf(RGBQUAD **&inf, unsigned int height) {
    for (unsigned int i = 0; i < height; ++i) {
        delete[] inf[i];
    }
    delete[] inf;
    inf = nullptr;
}
