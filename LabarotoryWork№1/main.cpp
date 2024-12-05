/*
    Andrew Sergienko st135882@student.spbu.ru
*/
#include "bmp_reader.h"
#include "filters.h"
#include <iostream>
#include <string>

int main()
{
    // Request the user for the path to the image
    std::string input_filename;
    std::cout << "Enter the path to the BMP file: ";
    std::getline(std::cin, input_filename);

    BMP_File bmp_file;

    // Attempt to load a BMP file, the name is passed from the user
    if (!bmp_file.Load_BMP_File(input_filename.c_str()))
    {
        std::cerr << "Failed to load BMP file: " << input_filename << std::endl;
        return -1;  // Terminate the program with an error
    }
    std::cout << "BMP File loaded successfully." << std::endl;

    // Apply a Gaussian filter to the original image
    ApplyGaussianFilter(&bmp_file, 5, 3.0);  // 5 - kernel size, 3.0 - sigma value
    bmp_file.Save_BMP_File("BMP_filtered.bmp");  // Save the filtering result

    // Counterclockwise rotation
    auto new_bmp_file_1 = FlipBMP90CounterClockwise(bmp_file);
    new_bmp_file_1->Save_BMP_File("BMP_counterclockwise.bmp");
    new_bmp_file_1.reset(); // Delete object

    // Clockwise rotation
    auto new_bmp_file_2 = FlipBMP90Clockwise(bmp_file);
    new_bmp_file_2->Save_BMP_File("BMP_clockwise.bmp");
    new_bmp_file_2.reset(); // Delete object
    return 0;
}
