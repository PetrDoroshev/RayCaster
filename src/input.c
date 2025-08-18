#include "input.h"
#include "math.h"

void keyDown(SDL_KeyboardEvent* event, int* keyboard) {

    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
        
        keyboard[event->keysym.scancode] = 1;
    }
}

void keyUp(SDL_KeyboardEvent* event, int* keyboard) {

    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {

        keyboard[event->keysym.scancode] = 0;
    }
}

void doInput(SDL_Event event, int* keyboard) {
    
    switch (event.type) {

        case SDL_KEYDOWN:
            keyDown(&event.key, keyboard);
            break;
        case SDL_KEYUP:
            keyUp(&event.key, keyboard);
            break;
        default:
            break;
    }
}
