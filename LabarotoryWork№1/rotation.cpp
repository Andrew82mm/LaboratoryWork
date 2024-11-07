/* Sergienko Andrey b82 group st135882@student.spbu.ru */
#include "rotation.h"
#include <iostream>

RGBQUAD **rotate90Clockwise(RGBQUAD **rgbInfo, unsigned int width, unsigned int height)
{
    RGBQUAD **rotated = new RGBQUAD*[width];
    for (unsigned int i = 0; i < width; ++i)
    {
        rotated[i] = new RGBQUAD[height];
    }

    for (unsigned int i = 0; i < height; ++i)
    {
        for (unsigned int j = 0; j < width; ++j)
        {
            rotated[j][height - i - 1] = rgbInfo[i][j];
        }
    }

    return rotated;
}

RGBQUAD **rotate90CounterClockwise(RGBQUAD **rgbInfo, unsigned int width, unsigned int height)
{
    RGBQUAD **rotated = new RGBQUAD*[width];
    for (unsigned int i = 0; i < width; ++i)
    {
        rotated[i] = new RGBQUAD[height];
    }

    for (unsigned int i = 0; i < height; ++i)
    {
        for (unsigned int j = 0; j < width; ++j)
        {
            rotated[width - j - 1][i] = rgbInfo[i][j];
        }
    }

    return rotated;
}
