#ifndef SG_TEST_DRAW_H
#define SG_TEST_DRAW_H

#include "SDL.h"
#include "defs.h"
#include <math.h>

void drawMap(SDL_Renderer* renderer, int map[MAP_WIDTH][MAP_HEIGHT]);
void prepareScene(uint32_t *pixels, uint32_t color);
void presentScene(SDL_Renderer* renderer, SDL_Texture* texture, uint32_t* pixels);
void drawWallLine(uint32_t *pixels, int x, int side, uint32_t color, uint32_t height);
void drawTextureSlice(uint32_t *pixels, SDL_Surface *texture, int x, uint32_t wall_x, int side, uint32_t line_height);
void drawPlayerOnMap(SDL_Renderer* renderer, int player_x, int player_y);
void drawRayOnMap(SDL_Renderer* renderer, double ray_dir_x, double ray_dir_y, double ray_length, int player_x, int player_y);
void drawText(SDL_Renderer* renderer, char* text, uint32_t pos_x, uint32_t pos_y, SDL_Color color);

#endif //SG_TEST_DRAW_H
