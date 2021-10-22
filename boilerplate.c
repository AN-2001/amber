#include "boilerplate.h"


// progress bar stuff //
#define NUM_PROGRESS_BARS 40
#define PRINT_PERIOD 20
#define FULL '='
#define ARROW '>'
#define EMPTY '-'
#define GO_TO_LINE_START "[0`"
#define OUT_SIZE  256

void printProgress(int curr, int total){
	double precentage = (double)curr/total;
	int numFull = precentage * NUM_PROGRESS_BARS;
	printf("%s", GO_TO_LINE_START);
	for(int i = 0; i < NUM_PROGRESS_BARS; i++){
		putc(i <= numFull ? (i == numFull ? ARROW : FULL)  : EMPTY, stdout);
	}
	printf("|%3d%%", (int)(precentage * 100));
	fflush(stdout);
}

int outputImage(gdImage *img, const char *path, int i, int total){
	if(!img || !path)
		return 0;
	char out[OUT_SIZE] = {0};
	if(total == 1){
		printProgress(total, total);
		sprintf(out, "%s.png", path);
		gdImageFile(img, out);
		return total;
	}

	if(i % PRINT_PERIOD == 0)
		printProgress(i, total);
	sprintf(out, "%s%d.png", path, i);
	gdImageFile(img, out);
	return i;
}
