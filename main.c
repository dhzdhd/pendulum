#include "raylib.h"
#include "raymath.h"

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

int main(void)
{
    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;
    const float GRAVITY = 9.8f;
    const int ZERO_WIDTH = SCREEN_WIDTH / 2;
    const int ZERO_HEIGHT = SCREEN_HEIGHT / 2 - 50;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The Pendulum");

    Rod rodInst = {
        (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50},
        (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50},
        0,
        GREEN,
        100,
    };

    bool simulation = false;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        Bob bobInst = {
            10,
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
            if (IsKeyDown(KEY_LEFT))
            {
                if (rodInst.angle > -90)
                {
                    rodInst.angle -= 1.0f;
                    rodInst.end.x = ZERO_WIDTH + (sin(rodInst.angle * DEG2RAD) * rodInst.length);
                    rodInst.end.y = ZERO_HEIGHT + (cos(rodInst.angle * DEG2RAD) * rodInst.length);
                }
            }
            if (IsKeyDown(KEY_RIGHT))
            {
                if (rodInst.angle < 90)
                {
                    rodInst.angle += 1.0f;
                    rodInst.end.x = ZERO_WIDTH + (sin(rodInst.angle * DEG2RAD) * rodInst.length);
                    rodInst.end.y = ZERO_HEIGHT + (cos(rodInst.angle * DEG2RAD) * rodInst.length);
                }
            }
        }

        if (simulation)
        {
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
