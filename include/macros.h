#ifndef MACROS_H_
#define MACROS_H_

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define GRID_WIDTH 10
#define GRID_HEIGHT 10

#define TILE_ORIGIN_X (WINDOW_WIDTH * .5f)
#define TILE_ORIGIN_Y 125.f

#define TILE_WIDTH 64.f
#define TILE_HEIGHT 32.f

#define TRANSLATE_X(x, y) (((x)-(y)) * (TILE_WIDTH * .5f) + TILE_ORIGIN_X)
#define TRANSLATE_Y(x, y) (((x)+(y)) * (TILE_HEIGHT * .5f) + TILE_ORIGIN_Y)

#endif
