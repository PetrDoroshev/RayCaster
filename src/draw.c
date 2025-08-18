#include "draw.h"
#include "SDL.h"
#include <string.h>
#include <stdio.h>

void drawMap(SDL_Renderer* renderer, int map[MAP_WIDTH][MAP_HEIGHT]) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int k = 0; k < MAP_WIDTH; k++){
            if (map[i][k] > 0){
                SDL_Rect rect = {MINIMAP_X + MINIMAP_CELL_SIZE * k,
                                 MINIMAP_Y + MINIMAP_CELL_SIZE * i,
                                 MINIMAP_CELL_SIZE,
                                 MINIMAP_CELL_SIZE};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void drawPlayerOnMap(SDL_Renderer* renderer, int player_x, int player_y){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_Rect rect = {MINIMAP_X + (player_x * MINIMAP_CELL_SIZE) / TILE_SIZE,
                     MINIMAP_Y + (player_y * MINIMAP_CELL_SIZE) / TILE_SIZE,
                     MINIMAP_CELL_SIZE / 2,
                     MINIMAP_CELL_SIZE / 2};
    SDL_RenderFillRect(renderer, &rect);
}

void drawRayOnMap(SDL_Renderer* renderer, double ray_dir_x, double ray_dir_y, double ray_length, int player_x, int player_y){
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);

    float player_map_x = MINIMAP_X + (float)(player_x * MINIMAP_CELL_SIZE) / TILE_SIZE;
    float player_map_y = MINIMAP_Y + (float)(player_y * MINIMAP_CELL_SIZE) / TILE_SIZE;

    ray_length = (ray_length * MINIMAP_CELL_SIZE) / TILE_SIZE;

    SDL_RenderDrawLineF(renderer,
                        player_map_x,
                        player_map_y,
                        (float)(player_map_x + ray_length * ray_dir_x),
                        (float)(player_map_y - ray_length * ray_dir_y));

}


void drawWallLine(uint32_t *pixels, int x, int side, uint32_t color, uint32_t height) {

    int half_height = (int)height / 2;

    uint32_t y0 = SCREEN_HEIGHT_HALF - half_height > 0 ? SCREEN_HEIGHT_HALF - half_height : 0;
    uint32_t y1 = SCREEN_HEIGHT_HALF + half_height < SCREEN_HEIGHT ? SCREEN_HEIGHT_HALF + half_height : SCREEN_HEIGHT - 1;

    if (side == 1) {
        color = (color >> 1) & 8355711;
    }
    for (uint32_t y = y0; y <= y1; y++) {
        pixels[y * SCREEN_WIDTH + x] = color;
    }
}

void drawTextureSlice(uint32_t *pixels, SDL_Surface *texture, int x, uint32_t wall_x, int side, uint32_t line_height) {

    uint32_t half_height = (uint32_t)line_height / 2;
    uint32_t y0 = SCREEN_HEIGHT_HALF - half_height;
    uint32_t y1 = SCREEN_HEIGHT_HALF + half_height;
    uint32_t tex_x = wall_x;
    uint32_t offset = 0;
    uint32_t color;

    if (line_height > SCREEN_HEIGHT) {
        y0 = 0;
        y1 = SCREEN_HEIGHT - 1;
        offset = half_height - SCREEN_HEIGHT_HALF;
    }

    double step = 1.0 * texture->h / line_height;
    double tex_y = step * offset;

    for (uint32_t y = y0; y < y1; y++) {

        color = ((uint32_t*)texture->pixels)[(uint32_t)tex_y * texture->w + tex_x];
        if (side == 1) {
            color = (color >> 1) & 8355711;
        }

        pixels[y * SCREEN_WIDTH + x] = color;
        tex_y += step;
    }

}

void prepareScene(uint32_t *pixels, uint32_t color) {

    SDL_memset4(pixels, color, SCREEN_HEIGHT * SCREEN_WIDTH);
}

void presentScene(SDL_Renderer* renderer, SDL_Texture* texture, uint32_t* pixels) {
    SDL_UpdateTexture(texture, NULL, pixels, SCREEN_WIDTH * sizeof(uint32_t));
    SDL_RenderCopyEx(renderer, texture, NULL, NULL, 0.0, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);
}



