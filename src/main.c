#include "raylib.h"
#include "raymath.h"
#include "sim.h"
#include "raygui.h"
#include <stdio.h>

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pendulum");

    Rod rodInst = {
        (Vector2){ZERO_WIDTH, ZERO_HEIGHT},
        (Vector2){ZERO_WIDTH, ZERO_HEIGHT + 400},
        0,
        (Color){136, 192, 208, 255},
        400,
    };

    bool simulation = false;
    Vector2 mousePos;
    float amplitude;

    float counter = 0.1f;
    float counterIncrement = 0.1f;

    float damper = 0.0f;

    int pointNumber = 0;
    Point pointList[10000];

    char buttonText[50] = "Start";

    SetTargetFPS(60);

    // GUI style settings
    GuiSetStyle(SLIDER, SLIDER_PADDING, 2);
    GuiSetStyle(SLIDER, BASE_COLOR_NORMAL, ColorToInt((Color){46, 52, 64, 255}));
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt((Color){46, 52, 64, 255}));
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt((Color){46, 52, 64, 255}));
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt((Color){46, 52, 64, 255}));
    GuiSetStyle(0, TEXT_SIZE, 20);

    // Uncomment for a slightly different slider look
    //    GuiSetStyle(SLIDER, BORDER_COLOR_NORMAL, ColorToInt((Color){218, 172, 209, 255}));
    //    GuiSetStyle(0, TEXT_COLOR_NORMAL, ColorToInt((Color){218, 172, 209, 255}));

    while (!WindowShouldClose())
    {
        // Update
        Bob bobInst = {
            30,
            (Vector2){
                rodInst.end.x,
                rodInst.end.y,
            },
            (Color){136, 192, 208, 255},
            (Vector2) {0, 0},
            1.0f,
        };
        bobInst.position.x += bobInst.velocity.x;
        bobInst.position.y += bobInst.velocity.y;

        // Start-Stop simulation on space key press
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
            amplitude = rodInst.angle;
            counter = 0.1f;

            // Reset particle number after simulation is paused
            pointNumber = 0;
        }
        else
        {
            // Physics
            rodInst.angle = amplitude * cos(sqrt(GRAVITY / rodInst.length) * counter);

            // Reduce amplitude according to damp value
            if (amplitude > 0.0f)
            {
                amplitude -= damper;
            }
            else
            {
                amplitude = 0.0f;
            }

            rodInst.end.x = ZERO_WIDTH + (sin(rodInst.angle) * rodInst.length);
            rodInst.end.y = ZERO_HEIGHT + (cos(rodInst.angle) * rodInst.length);
            counter += counterIncrement;
        }

        // Draw
        BeginDrawing();

        ClearBackground((Color){46, 52, 64, 255});
        DrawFPS(0, 0);
        DrawLine(rodInst.start.x, rodInst.start.y, rodInst.end.x, rodInst.end.y, rodInst.color);
        DrawCircle(bobInst.position.x, bobInst.position.y, bobInst.radius, bobInst.color);

        if (simulation)
        {
            pointList[pointNumber % POINT_LIMIT] = (Point){1.5, rodInst.end, 1.f};
            pointNumber++;

            // Drawing points
            for (int i = 0; i < POINT_LIMIT; i++)
            {
                DrawCircle(
                        pointList[i].position.x,
                        pointList[i].position.y,
                        pointList[i].radius,
                        ColorAlpha((Color) {218, 172, 209, 255}, pointList[i].opacity)
                );

                // Fade points after some interval of time
                if(pointList[i].opacity != 0.0f)
                {
                    pointList[i].opacity -= 0.003f;
                }
            }

            // Text showing damp, particle count
            char particleBuffer[100];
            sprintf(particleBuffer, "Particles: %d", pointNumber);
            DrawText(particleBuffer, SCREEN_WIDTH - 180, 0, 20, (Color) {218, 172, 209, 255});
            char dampBuffer[100];
            sprintf(dampBuffer, "Damping: %.4f", damper);
            DrawText(dampBuffer, SCREEN_WIDTH - 180, 20, 20, (Color) {218, 172, 209, 255});
        }

        // Sliders
        damper = GuiSliderPro(
            (Rectangle){SCREEN_WIDTH - 250, SCREEN_HEIGHT - 70, 200, 50},
            "Damping",
            "",
            damper,
            0,
            0.005f,
            20
        );
        counterIncrement = GuiSliderPro(
            (Rectangle){SCREEN_WIDTH - 250, SCREEN_HEIGHT - 140, 200, 50},
            "Speed",
            "",
            counterIncrement,
            0.05f,
            0.2f,
            20
        );

        // Start-Stop button
        if (GuiButton(
            (Rectangle){50, SCREEN_HEIGHT - 140, 200, 100},
            buttonText
        ))
        {
            if (!simulation)
            {
                strcpy(buttonText, "Stop");
            }
            else
            {
                strcpy(buttonText, "Start");
            }
            simulation = !simulation;
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
