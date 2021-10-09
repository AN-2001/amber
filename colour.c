#include "colour.h"
#include <gd.h>
#include "config.h"
#define DRAW_RECT_AT(img, x, y) (gdImageFilledRectangle(img, x, y, x + GRID_SIZE, y + GRID_SIZE, currentColor)) 
#define BUFFER_SIZE 512
#define MAX_P_COUNT 32	
struct palette_t{
	Color *p;
	unsigned count;
};

static Color currentColor = 0x0;
static Palette currPalette = NULL;

void setBackground(gdImage *img, Cindex index){
	if(!currPalette)
		return;
	for(int i = 0; i < img->sx; i++)
		for(int j = 0; j < img->sy; j++)
			gdImageFill(img,i, j, currPalette->p[index]);
}

void atomsDraw(Atom *atoms, size_t count, gdImage *img){
	for(int i = 0; i < count; i++){
		Atom atom = atoms[i];
		if(atom.cindex >= currPalette->count)
			return;

		currentColor = currPalette->p[atom.cindex];
		DRAW_RECT_AT(img, atom.pos.x, atom.pos.y);
	}
}

Palette paletteLoad(const char *csvPath){
	Palette p = malloc(sizeof(*p));
	if(!p)
		return NULL;
	p->p = malloc(sizeof(*p->p) * MAX_P_COUNT);
	if(!p->p){
		free(p);
		return NULL;
	}

	FILE *csv = fopen(csvPath, "r");
	if(!csv){
		free(p);
		return NULL;
	}
	char c, currCol[BUFFER_SIZE];
	while(!feof(csv)){
		int i = 0;	
		while( (c = fgetc(csv)) != ','){
			if(c == EOF)
				break;
			currCol[i++] = c;
		}
		currCol[i] = '\0';
		p->p[p->count++] = strtol(currCol, NULL, 16);
	}
	printf("loaded %s with %d colours\n", csvPath, p->count);

	return p;

}
void paletteFree(Palette p){
	free(p);
}
void paletteSet(Palette p){
	if(!p)
		return;
	currPalette = p;
}

int paletteGetCount(Palette p){
	if(!p)
		return 0;
	return p->count;
}
