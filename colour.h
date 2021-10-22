#ifndef COLOUR_H
#define COLOUR_H
#include "vec.h"
#include <gd.h>
// TODO: remove all things unrelated to colour
typedef int Color;
typedef unsigned Cindex;
typedef struct{
	Vec2 pos;
	Cindex cindex;
} Atom;

typedef struct palette_t *Palette;

// draws an array of atoms into img
void atomsDraw(Atom *atom, size_t count, gdImage *img);

// sets the image background using the index from the current palette
void setBackground(gdImage *img, Cindex index);

// loads a palette from a CSV file
Palette paletteLoad(const char *csvPath);

// frees a palette
void paletteFree(Palette p);

// sets the current palette
void paletteSet(Palette p);

// gets the number of colours in p
int paletteGetCount(Palette p);

#endif // COLOUR_H
