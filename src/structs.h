#ifndef SG_TEST_STRUCTS_H
#define SG_TEST_STRUCTS_H

#include "defs.h"

typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Texture* texture;
    uint32_t pixels[SCREEN_HEIGHT * SCREEN_WIDTH];
    uint32_t keyboard[MAX_KEYBOARD_KEYS];
} App;

typedef struct {
    double x;
    double y;
    double dir_x;
    double dir_y;
    double speed;
    double rotation_speed;
} Player;


#endif //SG_TEST_STRUCTS_H
