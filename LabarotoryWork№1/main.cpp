/*
    Andrew Sergienko st135882@student.spbu.ru
*/

#include "bmp_file.h"
#include "filter.h"
#include <iostream>
#include <string>

int main()
{
    std::string input_filename;
    std::cout << "Enter the path to the BMP file: ";
    std::getline(std::cin, input_filename);

    BMP_File bmp_file;

    if (!bmp_file.Load_BMP_File(input_filename.c_str()))
    {
        std::cerr << "Failed to load BMP file: " << input_filename << std::endl;
        return -1;
    }
    std::cout << "BMP File loaded successfully." << std::endl;

    {
        BMP_File bmp_copy;
        Filter filter(5, 3.0);
        auto filtered_bmp = Filter::ApplyGaussianFilter(bmp_file, filter);
        filtered_bmp->Save_BMP_File("BMP_filtered.bmp");
    }

    {
        BMP_File bmp_copy;
        bmp_copy.Load_BMP_File(input_filename.c_str());
        auto rotated_bmp_ccw = Filter::FlipBMP90CounterClockwise(bmp_copy);
        rotated_bmp_ccw->Save_BMP_File("BMP_counterclockwise.bmp");
    }

    {
        BMP_File bmp_copy;
        bmp_copy.Load_BMP_File(input_filename.c_str());
        auto rotated_bmp_cw = Filter::FlipBMP90Clockwise(bmp_copy);
        rotated_bmp_cw->Save_BMP_File("BMP_clockwise.bmp");
    }

    return 0;
}

