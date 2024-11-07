/* Sergienko Andrey b82 group st135882@student.spbu.ru */
#include "write.h"
#include <iostream>

bool writeBMP(const char *fileName, const BITMAPFILEHEADER &fileHeader, const BITMAPINFOHEADER &fileInfoHeader, RGBQUAD **rgbInfo)
{
    std::ofstream fileStream(fileName, std::ios::binary);
    if (!fileStream)
    {
        std::cerr << "Error creating file '" << fileName << "'." << std::endl;
        return false;
    }

    fileStream.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
    fileStream.write(reinterpret_cast<const char*>(&fileInfoHeader), sizeof(fileInfoHeader));

    int width = fileInfoHeader.biWidth;
    int height = abs(fileInfoHeader.biHeight);
    int padding = (4 - (width * 3) % 4) % 4;

    fileStream.seekp(fileHeader.bfOffBits, std::ios::beg);

    for (int i = height - 1; i >= 0; --i)
    {
        for (int j = 0; j < width; ++j)
        {
            fileStream.write(reinterpret_cast<const char*>(&rgbInfo[i][j]), 3);
        }
        fileStream.write("\0\0\0", padding);
    }

    return true;
}

