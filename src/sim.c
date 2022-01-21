#include "sim.h"
#include "raylib.h"
#include "raymath.h"
#include <math.h>

float getAngleFromPos(Vector2 pos)
{
    float length = pos.y - ZERO_HEIGHT;
    float width = pos.x - ZERO_WIDTH;
    float angle = atan((width / length));


    if (fabsf(length) == length) {
        return angle;
    } else  {
        return 3.14 + angle;
    }
}

