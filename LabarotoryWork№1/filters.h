#ifndef FILTERS_H
#define FILTERS_H

#include "main.h"
// Манипуляции с картинкой надо вставить либо в сам класс картинки, либо в отдельный namespace или статический класс
void applyGaussianFilter(RGBQUAD **inf, unsigned int width, unsigned int height);

#endif
