#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simple Raylib Module");

    SetTargetFPS(60);

    Vector2 ballPosition = { (float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2 };
    Vector2 ballSpeed = { 6.0f, 60.0f };
    float ballRadius = 10.0f;

    while (!WindowShouldClose())
    {
        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;

        if ((ballPosition.x >= (SCREEN_WIDTH - ballRadius)) || (ballPosition.x <= ballRadius))
            ballSpeed.x *= -1.0f;
        if ((ballPosition.y >= (SCREEN_HEIGHT - ballRadius)) || (ballPosition.y <= ballRadius))
            ballSpeed.y *= -1.0f;

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawCircleV(ballPosition, ballRadius, MAROON);
            DrawText("Simple Raylib Example - Bouncing Ball", 10, 10, 20, DARKGRAY);
            DrawFPS(10, 40);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
