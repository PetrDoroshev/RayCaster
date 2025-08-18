#ifndef SG_TEST_INPUT_H
#define SG_TEST_INPUT_H

#include "SDL.h"
#include "defs.h"

void keyDown(SDL_KeyboardEvent* event, int* keyboard);
void keyUp(SDL_KeyboardEvent* event, int* keyboard);
void doInput(SDL_Event event, int* keyboard);

#endif //SG_TEST_INPUT_H
