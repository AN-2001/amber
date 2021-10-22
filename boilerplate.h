#ifndef BOILER_PLATE_H
#define BOILER_PLATE_H
#include <gd.h>

// just a progress bar kek
void printProgress(int curr, int total);
// outputs the image and writes the progress bar
int outputImage(gdImage *img, const char *path, int i, int total);

#endif // BOILER_PLATE_H
