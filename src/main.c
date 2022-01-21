#include "raylib.h"
#include "raymath.h"
#include "sim.h"

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
            0.0f,
            1.0f,
        };

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
                rodInst.angle = getAngleFromPos(mousePos, ZERO_HEIGHT, ZERO_WIDTH);
                rodInst.end.x = ZERO_WIDTH + (sin(rodInst.angle) * rodInst.length);
                rodInst.end.y = ZERO_HEIGHT + (cos(rodInst.angle) * rodInst.length);
            }
        }

        if (simulation)
        {
            // Physics
            if (abs(rodInst.angle) != rodInst.angle)
            {
                float lengthFromBaseY = abs(rodInst.end.y - ZERO_HEIGHT);
                float potentialE = bobInst.mass * GRAVITY * rodInst.length * sin(abs(rodInst.angle * DEG2RAD));
                float kineticE = 0;
            }
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
