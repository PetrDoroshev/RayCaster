#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <math.h>
#include <SDL.h>
#include <SDL_image.h>
#include "structs.h"
#include "init.h"
#include "input.h"
#include "draw.h"
#include "timer.h"

Player player = {4.5, 3.5, 0, 1, 0.11, (PI * 6) / 180};
App app;

int map[MAP_WIDTH][MAP_HEIGHT] = {
    
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,3,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

double plane_x, plane_y, PLANE_LENGTH;

void movePLayer();
double getLength(double x, double y);
SDL_Surface* loadImage(char const *path);

int main( int argc, char* args[] ) {

    SDL_Surface *textures[] = {
        
            SDL_ConvertSurfaceFormat(loadImage("../../../pics/redbrick.png"), SDL_PIXELFORMAT_ARGB8888, 0),
            SDL_ConvertSurfaceFormat(loadImage("../../../pics/bluestone.png"), SDL_PIXELFORMAT_ARGB8888, 0),
            SDL_ConvertSurfaceFormat(loadImage("../../../pics/colorstone.png"), SDL_PIXELFORMAT_ARGB8888, 0),
            SDL_ConvertSurfaceFormat(loadImage("../../../pics/wood.png"), SDL_PIXELFORMAT_ARGB8888, 0)
    };


    SDL_Surface *floor_texture = SDL_ConvertSurfaceFormat(loadImage("../../../pics/wood.png"), SDL_PIXELFORMAT_ARGB8888, 0);


    PLANE_LENGTH = tan(HALF_FOV);
    plane_x = 1; plane_y = 0;

    const uint32_t DISTANCE_TO_PLANE = (uint32_t)((SCREEN_WIDTH / 2.0) / PLANE_LENGTH);

    uint32_t colors[4] = {
            red,
            green,
            blue,
            white
    };

    initApp(&app);
    SDL_bool done = SDL_FALSE;

    while (!done) {

        prepareScene(app.pixels, black);
        movePLayer();

        for (int ray_count = 0; ray_count < SCREEN_WIDTH; ray_count++) {

            char hit = 0, side;

            double camera_x = 2.0 * ray_count / SCREEN_WIDTH - 1;
            double ray_dir_x = player.dir_x + plane_x * camera_x;
            double ray_dir_y = player.dir_y + plane_y * camera_x;

            uint32_t map_x = (uint32_t)player.x;
            uint32_t map_y = (uint32_t)player.y;

            double delta_dist_x = fabs(1 / ray_dir_x);
            double delta_dist_y = fabs(1 / ray_dir_y);

            double side_dist_x, side_dist_y, wall_distance;
            uint32_t step_x, step_y;

            //wall casting

            if (ray_dir_y > 0) {
                step_y = -1;
                side_dist_y = (player.y - map_y) * delta_dist_y;

            } else {
                step_y = 1;
                side_dist_y = (map_y + 1 - player.y) * delta_dist_y;
            }

            if (ray_dir_x < 0) {
                step_x = -1;
                side_dist_x = (player.x - map_x) * delta_dist_x;

            } else {
                step_x = 1;
                side_dist_x = (map_x + 1 - player.x) * delta_dist_x;
            }

            while (!hit) {

                if (side_dist_x < side_dist_y) {
                    side_dist_x += delta_dist_x;
                    map_x += step_x;
                    side = 0;

                } else {

                    side_dist_y += delta_dist_y;
                    map_y += step_y;
                    side = 1;
                }

                if (map[map_y][map_x] > 0) {
                    hit = 1;
                }
            }
            side_dist_x -= delta_dist_x;
            side_dist_y -= delta_dist_y;

            if (side == 0)
                wall_distance = fabs((player.dir_y * ray_dir_y + player.dir_x * ray_dir_x) * side_dist_x);
            else
                wall_distance = fabs((player.dir_y * ray_dir_y + player.dir_x * ray_dir_x) * side_dist_y);

            uint32_t wall_height = (uint32_t)((1 / wall_distance) * DISTANCE_TO_PLANE);

            double wall_x;

            if (side == 0) {
                wall_x = player.y - wall_distance * ray_dir_y;
            }
            else {
                wall_x = player.x + wall_distance * ray_dir_x;
            }

            if (side == 0 && ray_dir_x > 0) {
                wall_x = textures[0]->w - wall_x - 1;
            }
            if (side == 1 && ray_dir_y < 0) {
                wall_x = textures[0]->w - wall_x - 1;
            }

            wall_x -= floor(wall_x);
            uint32_t tex_x = (uint32_t)(textures[0]->w * wall_x);

            drawTextureSlice(app.pixels, textures[map[map_y][map_x] - 1], ray_count, tex_x, side, wall_height);

            
            //floor casting
            for (uint32_t h = SCREEN_HEIGHT_HALF + wall_height / 2; h < SCREEN_HEIGHT; h++) {
                


            }
        }

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT){
                done = SDL_TRUE;
            }
            doInput(event, app.keyboard);
        }
        drawMap(app.renderer, map);
        presentScene(app.renderer, app.texture, app.pixels);
    }

    quitApp(&app);
    return 0;
}




void movePLayer(){

    if (app.keyboard[SDL_SCANCODE_W]) {

        double new_y = player.y - (player.speed * player.dir_y);
        double new_x = player.x + (player.speed * player.dir_x);

        if (map[(uint32_t)player.y][(uint32_t)new_x] == 0) player.x = new_x;
        if (map[(uint32_t)new_y][(uint32_t)player.x] == 0) player.y = new_y;
    }

    if (app.keyboard[SDL_SCANCODE_S]) {

        double new_y = player.y + player.speed * player.dir_y;
        double new_x = player.x - player.speed * player.dir_x;

        if (map[(uint32_t)player.y][(uint32_t)new_x] == 0) player.x = new_x;
        if (map[(uint32_t)new_y][(uint32_t)player.x] == 0) player.y = new_y;
    }

    if (app.keyboard[SDL_SCANCODE_A]) {

        double new_y = player.y - player.speed * player.dir_x;
        double new_x = player.x - player.speed * player.dir_y;

        if (map[(uint32_t)player.y][(uint32_t)new_x] == 0) player.x = new_x;
        if (map[(uint32_t)new_y][(uint32_t)player.x] == 0) player.y = new_y;
    }

    if (app.keyboard[SDL_SCANCODE_D]) {

        double new_y = player.y + player.speed * player.dir_x;
        double new_x = player.x + player.speed * player.dir_y;

        if (map[(uint32_t)player.y][(uint32_t)new_x] == 0) player.x = new_x;
        if (map[(uint32_t)new_y][(uint32_t)player.x] == 0) player.y = new_y;

    }
    
    if (app.keyboard[SDL_SCANCODE_LEFT]) {
        double dir_x_tmp = player.dir_x;
        player.dir_x = player.dir_x * cos(player.rotation_speed) - player.dir_y * sin(player.rotation_speed);
        player.dir_y = player.dir_y * cos(player.rotation_speed) + dir_x_tmp * sin(player.rotation_speed);

        plane_x = PLANE_LENGTH * (player.dir_y);
        plane_y = PLANE_LENGTH * (-player.dir_x);

    }
    
    if (app.keyboard[SDL_SCANCODE_RIGHT]) {
        double dir_x_tmp = player.dir_x;
        player.dir_x = player.dir_x * cos(player.rotation_speed) + player.dir_y * sin(player.rotation_speed);
        player.dir_y = player.dir_y * cos(player.rotation_speed) - dir_x_tmp * sin(player.rotation_speed);

        plane_x = PLANE_LENGTH * (player.dir_y);
        plane_y = PLANE_LENGTH * (-player.dir_x);
    }
}

double getLength(double x, double y) {
    return sqrt(pow(x, 2) + pow(y, 2));
}

SDL_Surface* loadImage(char const *path) {

    SDL_Surface* surface = IMG_Load(path);
    
    if ( surface == NULL ){
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }

    return surface;
}





