#include "raylib.h"

#define RAYGUI_IMPLEMENTATION

#ifndef PENDULUM_SIM_H
#define PENDULUM_SIM_H

typedef struct Rod
{
    Vector2 start;
    Vector2 end;
    float angle;
    Color color;
    int length;
} Rod;

typedef struct Bob
{
    float radius;
    Vector2 position;
    Color color;
    Vector2 velocity;
    float mass;
} Bob;

typedef struct Point
{
    float radius;
    Vector2 position;
    float opacity;
} Point;

static const int SCREEN_WIDTH = 1920;
static const int SCREEN_HEIGHT = 1080;
static const float GRAVITY = 9.8f;
static const int ZERO_WIDTH = SCREEN_WIDTH / 2;
static const int ZERO_HEIGHT = SCREEN_HEIGHT / 2 - 50 ;

// Upper limit to list initialisation.
// Does not affect simulation of points in any way.
static const int POINT_LIMIT = 2000;  // < 10000

float getAngleFromPos(Vector2);

#endif
