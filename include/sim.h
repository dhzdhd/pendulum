#include "raylib.h"

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
    float velocity;
    float mass;
} Bob;

static const int SCREEN_WIDTH = 1920;
static const int SCREEN_HEIGHT = 1080;
static const float GRAVITY = 9.8f;
static const int ZERO_WIDTH = SCREEN_WIDTH / 2;
static const int ZERO_HEIGHT = SCREEN_HEIGHT / 2 - 200;

float getAngleFromPos(Vector2, int, int);

#endif
