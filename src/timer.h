#ifndef SG_TEST_TIMER_H
#define SG_TEST_TIMER_H

#include <stdint.h>
#include "SDL.h"


typedef struct {

    uint32_t startTicks;
    uint8_t Started;

} Timer;

void startTimer(Timer* timer);
void stopTimer(Timer* timer);
uint32_t getTicks(Timer* timer);




#endif //SG_TEST_TIMER_H
