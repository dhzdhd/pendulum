#include <math.h>

#include "sim.h"
#include "raylib.h"


float getAngleFromPos(Vector2 pos)
{
    float length = pos.y - ZERO_HEIGHT;
    float width = pos.x - ZERO_WIDTH;
    float angle = atan((width / length));

    if (fabsf(length) == length) {
        return angle;
    } else {
        return PI + angle;
    }
}

