#ifndef CONFIG_H
#define CONFIG_H
#define WIDTH (800)
#define HEIGHT (800)
#define GRID_SIZE 5
#define ATOM_SIZE 10
#define WS ((WIDTH) / (GRID_SIZE))
#define HS ((HEIGHT) / (GRID_SIZE))
#define ITERS 500
#define ATOM_COUNT 10000

// basic options
#define SHOW_ALL_ITERS
#define CIRCLE_ATOMS


// CURVE STUFF //
#define CURVE_COUNT 1
#define CURVE_STEP 0.0001f
#endif // CONFIG_H

