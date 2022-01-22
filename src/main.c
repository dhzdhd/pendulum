#include "raylib.h"
#include "raymath.h"
#include "sim.h"
#include <stdio.h>

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The Pendulum");

    Rod rodInst = {
        (Vector2){ZERO_WIDTH, ZERO_HEIGHT},
        (Vector2){ZERO_WIDTH, ZERO_HEIGHT + 400},
        0,
        GREEN,
        400,
    };

    bool simulation = false;
    Vector2 mousePos;
    float currentAngle;
    float counter = 0.1;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        Bob bobInst = {
            30,
            (Vector2){
                rodInst.end.x,
                rodInst.end.y,
            },
            GREEN,
            (Vector2) {0, 0},
            1.0f,
        };
        bobInst.position.x += bobInst.velocity.x;
        bobInst.position.y += bobInst.velocity.y;

        if (IsKeyPressed(KEY_SPACE))
        {
            simulation = !simulation;
        }

        if (!simulation)
        {
            // Move pendulum according to mouse movement
            if (IsMouseButtonDown(0))
            {
                mousePos = GetMousePosition();
                rodInst.angle = getAngleFromPos(mousePos);
                rodInst.end.x = ZERO_WIDTH + (sin(rodInst.angle) * rodInst.length);
                rodInst.end.y = ZERO_HEIGHT + (cos(rodInst.angle) * rodInst.length);
            }
            currentAngle = rodInst.angle;
        }

        if (simulation)
        {
            // Physics
            rodInst.angle = currentAngle * cos(sqrt(GRAVITY / rodInst.length) * counter);
            printf("%f", rodInst.angle);
            rodInst.end.x = ZERO_WIDTH + (sin(rodInst.angle) * rodInst.length);
            rodInst.end.y = ZERO_HEIGHT + (cos(rodInst.angle) * rodInst.length);
            counter += 0.1;
        }

        // Draw
        BeginDrawing();

        ClearBackground(BLACK);
        DrawLine(rodInst.start.x, rodInst.start.y, rodInst.end.x, rodInst.end.y, rodInst.color);
        DrawCircle(bobInst.position.x, bobInst.position.y, bobInst.radius, bobInst.color);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
