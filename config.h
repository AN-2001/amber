#ifndef CONFIG_H
#define CONFIG_H
#define WIDTH 1920
#define HEIGHT 1080
#define GRID_SIZE 5
#define ATOM_SIZE 5
#define WS ((WIDTH) / (GRID_SIZE))
#define HS ((HEIGHT) / (GRID_SIZE))
#define ITERS 2000
#define ATOM_COUNT 25000

// basic options
//#define SHOW_ALL_ITERS
//#define CIRCLE_ATOMS


// CURVE STUFF //
#define CURVE_COUNT 1
#define CURVE_STEP 0.0001f
#endif // CONFIG_H

// progress bar stuff //
#define NUM_PROGRESS_BARS 40
#define PRINT_PERIOD 20
#define FULL '='
#define ARROW '>'
#define EMPTY '-'
