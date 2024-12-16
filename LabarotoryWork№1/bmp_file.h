/*
    Andrew Sergienko st135882@student.spbu.ru
*/
#ifndef BMP_FILE_H
#define BMP_FILE_H

#include <cstdint>
#include <iostream>
#include <memory>

#pragma pack(push, 1)

class BMP_Header
{
public:
    uint8_t ID[2];
    uint32_t file_size;
    uint8_t unused[4];
    uint32_t pixel_offset;

    BMP_Header() = default;
};

class DIB_Header
{
public:
    uint32_t header_size;
    uint32_t width;
    uint32_t height;
    uint16_t color_planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t data_size;
    uint32_t print_resolution_x;
    uint32_t print_resolution_y;
    uint32_t colors_count;
    uint32_t important_colors;

    DIB_Header() = default;
};

class RGB
{
public:
    uint8_t blue;
    uint8_t green;
    uint8_t red;

    RGB(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) : blue(b), green(g), red(r) {}
};

class BMP_File
{
public:
    BMP_Header bmp_header;
    DIB_Header dib_header;
    RGB* file_data;

    BMP_File() : file_data(nullptr) {}

    ~BMP_File()
    {
        delete[] file_data;
    }

    bool Load_BMP_File(const char* file_name);
    void Save_BMP_File(const char* output_filename);
};

#pragma pack(pop)

#endif

