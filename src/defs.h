#ifndef SG_TEST_DEFS_H
#define SG_TEST_DEFS_H

#include "SDL.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH_HALF (SCREEN_WIDTH / 2)
#define SCREEN_HEIGHT_HALF (SCREEN_HEIGHT / 2)

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

#define PI 3.14159265358979323846
#define TWO_PI (PI * 2)

#define FOV (PI / 3)
#define HALF_FOV (FOV / 2)
#define TILE_SIZE 1

#define MAX_KEYBOARD_KEYS 350

#define MINIMAP_X 50
#define MINIMAP_Y 50
#define MINIMAP_CELL_SIZE 10

extern const uint32_t red;
extern const uint32_t green;
extern const uint32_t blue;
extern const uint32_t white;
extern const uint32_t black;

#endif //SG_TEST_DEFS_H
