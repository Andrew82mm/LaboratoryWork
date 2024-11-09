#include "rotation.h"
#include <iostream>

RGBQUAD **rotate90Clockwise(RGBQUAD **inf, unsigned int width, unsigned int height) {
    RGBQUAD **rotated = new RGBQUAD*[width];
    for (unsigned int i = 0; i < width; ++i) {
        rotated[i] = new RGBQUAD[height];
    }

    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            rotated[j][height - i - 1] = inf[i][j];
        }
    }

    return rotated;
}

RGBQUAD **rotate90CounterClockwise(RGBQUAD **inf, unsigned int width, unsigned int height) {
    RGBQUAD **rotated = new RGBQUAD*[width];
    for (unsigned int i = 0; i < width; ++i) {
        rotated[i] = new RGBQUAD[height];
    }

    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            rotated[width - j - 1][i] = inf[i][j];
        }
    }

    return rotated;
}
