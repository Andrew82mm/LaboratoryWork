#ifndef ROTATION_H
#define ROTATION_H

#include "main.h"

RGBQUAD **rotate90Clockwise(RGBQUAD **rgbInfo, unsigned int width, unsigned int height);
RGBQUAD **rotate90CounterClockwise(RGBQUAD **rgbInfo, unsigned int width, unsigned int height);

#endif 
