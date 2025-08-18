#include "init.h"

void initApp(App* app){

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        exit(1);
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {

        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        exit(1);
    }

    app->window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if ( app->window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        exit(1);
    }

    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetVSync(app->renderer, 1);

    if ( app->renderer == NULL ){
        printf("Can't create renderer %s", SDL_GetError());
        exit(1);
    }

    app->texture = SDL_CreateTexture(app->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
                                     SCREEN_WIDTH, SCREEN_HEIGHT);

    if ( app->texture == NULL ) {
        printf("Can't create texture %s", SDL_GetError());
        exit(1);
    }
}

void quitApp(App* app){

    SDL_DestroyTexture(app->texture);
    SDL_DestroyWindow(app->window);
    SDL_DestroyRenderer(app->renderer);

    SDL_Quit();
}


