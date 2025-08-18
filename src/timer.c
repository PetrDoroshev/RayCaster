#include "SDL.h"
#include "timer.h"


void startTimer(Timer* timer) {
    timer->Started = 1;
    timer->startTicks = SDL_GetTicks();
}

void stopTimer(Timer* timer) {
    timer->Started = 0;
    timer->startTicks = 0;
}

uint32_t getTicks(Timer* timer) {
    uint32_t time = 0;

    if (timer->Started) {

        time = SDL_GetTicks() - timer->startTicks;
    }

    return time;
}