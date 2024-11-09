#ifndef ROTATION_H
#define ROTATION_H

#include "main.h"

RGBQUAD **rotate90Clockwise(RGBQUAD **inf, unsigned int width, unsigned int height);
RGBQUAD **rotate90CounterClockwise(RGBQUAD **inf, unsigned int width, unsigned int height);

#endif 
