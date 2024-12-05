/*
    Andrew Sergienko st135882@student.spbu.ru
*/
#include "bmp_reader.h"
#include <iostream>
#include <fstream>

// Method for loading BMP file
bool BMP_File::Load_BMP_File(const char* file_name)
{
    std::ifstream file(file_name, std::ios::binary);
    if (!file)
    {
        std::cerr << "Unable to open file: " << file_name << std::endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&bmp_header), sizeof(BMP_Header));
    file.read(reinterpret_cast<char*>(&dib_header), sizeof(DIB_Header));

    file_data = new RGB[dib_header.width * dib_header.height];

    int row_size = ((dib_header.width * dib_header.bits_per_pixel + 31) / 32) * 4;
    file.seekg(bmp_header.pixel_offset, std::ios::beg);

    for (int y = dib_header.height - 1; y >= 0; --y)
    {
        file.read(reinterpret_cast<char*>(&file_data[y * dib_header.width]), dib_header.width * sizeof(RGB));
        file.seekg(row_size - dib_header.width * sizeof(RGB), std::ios::cur);
    }

    file.close();
    return true;
}

// Method for save new file
void BMP_File::Save_BMP_File(const char* output_filename)
{
    std::ofstream file(output_filename, std::ios::binary);
    if (!file)
    {
        std::cerr << "Unable to open file for writing: " << output_filename << std::endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(&bmp_header), sizeof(BMP_Header));
    file.write(reinterpret_cast<const char*>(&dib_header), sizeof(DIB_Header));

    file.seekp(dib_header.header_size + 14, std::ios::beg);

    int row_size = ((dib_header.width * dib_header.bits_per_pixel + 31) / 32) * 4;
    uint32_t padding = row_size - (dib_header.width * sizeof(RGB));

    for (int y = dib_header.height - 1; y >= 0; --y)
    {
        file.write(reinterpret_cast<const char*>(&file_data[y * dib_header.width]), dib_header.width * sizeof(RGB));
        for (uint32_t p = 0; p < padding; ++p)
        {
            file.put(0);
        }
    }

    file.close();
    std::cout << "Image saved successfully to " << output_filename << std::endl;
}

