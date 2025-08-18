#include "raycast.h"

static const double plane_length = tan(HALF_FOV);
static double plane_x = 1, plane_y = 0;

static const uint32_t DISTANCE_TO_PLANE = (uint32_t)((SCREEN_WIDTH / 2.0) / plane_length);














