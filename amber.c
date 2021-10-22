#include <stdio.h>
#include <gd.h>
#include <math.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include "vec.h"
#include "colour.h"
#include "config.h"
#include "boilerplate.h"
// TODO: get rid of globals you idiot.......
typedef Vec2 (*Curve)(double t);
Vec2 field[WS * HS];
Atom atoms[ATOM_COUNT];
void performIter();
void initField();
void initAtoms(int p);
void setVec(Vec2 v, Vec2 u, int norm);


#define NUM_ARGS 2
const char * help[NUM_ARGS][2] = {{"-o", "set the output file"},
						          {"-p", "set the palette"}};
// the index inside argv[]
int pathi = -1, palettei = -1;
void parseArgs(int argc, const char *argv[]);
void printHelp();

int main(int argc, const char *argv[]){
	parseArgs(argc, argv);
	const char *path = (pathi != -1 ? argv[pathi] : "out");	
	const char *palettePath = (palettei != -1 ? argv[palettei] : "default.csv");	

	Palette pal = paletteLoad(palettePath);	
	if(!pal)
		return 1;
	paletteSet(pal);

	srand(time(NULL));
	gdImage *img = gdImageCreateTrueColor(WIDTH, HEIGHT);
	if(!img)
		return 1;
	setBackground(img, 0);
	initField();
	initAtoms(paletteGetCount(pal));
	for(int i = 0; i < ITERS; i++){
		performIter();
		atomsDraw(atoms, ATOM_COUNT, img);
#ifdef SHOW_ALL_ITERS
		outputImage(img, path, i, ITERS);
#else
		printProgress(i, ITERS);
#endif
	}
	printProgress(ITERS, ITERS);
#ifndef SHOW_ALL_ITERS
	outputImage(img, path, 1, 1);
#endif

	gdImageDestroy(img);
	paletteFree(pal);
	return 0;
}

void performIter(){
	for(int i = 0; i < ATOM_COUNT; i++){
		int gx = (int)(atoms[i].pos.x / GRID_SIZE),
		    gy = (int)(atoms[i].pos.y / GRID_SIZE);
		gx = fmin(fmax(0, gx), WS - 1);
		gy = fmin(fmax(0, gy), HS - 1);

		Vec2 vec = field[gx + gy * WS];

		atoms[i].pos.x += vec.x;
		atoms[i].pos.y += vec.y;
		atoms[i].pos.x = fmin(fmax(atoms[i].pos.x, 0), WIDTH);
		atoms[i].pos.y = fmin(fmax(atoms[i].pos.y, 0), HEIGHT);
	}
}


void setVec(Vec2 v, Vec2 u, int norm){
	int x = (int)(v.x / GRID_SIZE),
		y = (int)(v.y / GRID_SIZE);
	x = fmin(fmax(x, 0), WS - 1);
	y = fmin(fmax(y, 0), HS - 1);
	int index = x + y * WS;
	if(norm)
		u = vecNorm(u);
	field[index] = u;
}

void initField(){
	for(int i = 0; i < WS; i++){
		for(int j = 0; j < HS; j++){
			int sx = i * GRID_SIZE,
				sy = j * GRID_SIZE;
			//Vec2 v = VEC_CREATE(cos((sx - sy * 2) * 0.0009f), sin((sy + sx) * 0.0021f));
			double zoom = 0.4f;
			Vec2 v = VEC_CREATE(sin((i+j) * 0.019 * zoom), (cos((i-j) * 0.028f * zoom)));
			setVec(VEC_CREATE(sx, sy), v, 1);
		}
	}
}

void initAtoms(int p){
	for(int i = 0; i < ATOM_COUNT; i++){
		atoms[i].cindex = rand() % p;
		atoms[i].pos = VEC_CREATE(rand() % WIDTH, rand() % HEIGHT);
	}
}



/// FOR CUSTOM CURVES, U CAN IGNORE FOR NOW///////
Vec2 spiral(double t){
	return VEC_CREATE(200 + 200 * (t*t) * cos(t * 64 * M_PI),
			          200 + 200 * (t*t) * sin(t * 64 * M_PI));
}
Vec2 spirald(double t){
	return VEC_CREATE(200 * 2 * t * cos(t * 64 * M_PI) - 64 * M_PI * 200 * t * t * sin(t * 64 * M_PI),
			          200 * 2 * t * sin(t * 64 * M_PI) + 64 * M_PI * 200 * t * t * cos(t * 64 * M_PI));
}
const Curve curves[CURVE_COUNT] = {spiral};
const Curve dervs[CURVE_COUNT] = {spirald};


void loadCurves(){
	for(int i = 0; i < CURVE_COUNT; i++){
		for(double t = 0; t <= 1; t += CURVE_STEP){
			Vec2 v = curves[i](t);
			Vec2 d = dervs[i](t);
			Vec2 perp = VEC_CREATE(-d.y, d.x);
			perp = vecNorm(perp);		
			for(double s = -1; s <= 1; s += CURVE_STEP){
				Vec2 added = VEC_CREATE(v.x + perp.x * 50 * s,
						                v.y + perp.y * 50 * s);
				setVec(added, d, 1);
			}
		}
	}
}


void parseArgs(int argc, const char *argv[]){
	for(int i = 0; i < argc; i++){
		if(argv[i][0] == '-'){
			switch(argv[i][1]){
				case 'p':
				case 'P':
					palettei = i + 1;
					break;
				case 'o':
				case 'O':
					pathi = i + 1;
					break;
				case 'h':
				case 'H':
					printHelp();
					exit(0);
					break;
			}
		}
	}
}


void printHelp(){
	printf("skeleton: put simple description here\n");
	for(int i = 0; i < NUM_ARGS; i++){
		printf("%s : %s\n", help[i][0], help[i][1]);		
	}
}
