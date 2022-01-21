#include "sim.h"
#include "raylib.h"
#include "raymath.h"

float getAngleFromPos(Vector2 pos, int zeroHeight, int zeroWidth)
{
    float length = pos.y - zeroHeight;
    float width = pos.x - zeroWidth;
    float angle = atan(width / length);

    return angle;
}

