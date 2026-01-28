#include "raylib.h"
#include <assert.h>

constexpr int INITIAL_SCREEN_WIDTH = 800;
constexpr int INITIAL_SCREEN_HEIGHT = 450;
constexpr int TARGET_FPS = 60;
constexpr double DELTAT = 1. / TARGET_FPS;

typedef struct ball {
    Vector2 position;
    Vector2 speed;
    Vector2 acceleration;
    float radius;
} Ball;

float Clamp(float d, float min, float max) {
    const float t = d < min ? min : d;
    return t > max ? max : t;
}
void moveBall(Ball *ball);
bool wallColision(Ball *ball);
float meterToPixel(float m);
float pixelToMeter(float p);

int main(void) {

    InitWindow(INITIAL_SCREEN_WIDTH, INITIAL_SCREEN_HEIGHT,
               "Simple Raylib Module");

    SetTargetFPS(TARGET_FPS);

    Ball ball = {.position = {400.0f, 225.0f},
                 .speed = {200.0f, 200.0f},
                 .acceleration = {0.0f, 3000.0f},
                 .radius = 20.0f};

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_A)) {
            ball.radius *= 2;
        }
        moveBall(&ball);
        wallColision(&ball);

        // TODO: fix this shit
        // assert(ballPosition.x >= ballRadius && "Ball X position is out of
        // left bound"); assert(ballPosition.x <= GetScreenWidth() - ballRadius
        // && "Ball X position is out of right bound"); assert(ballPosition.y >=
        // ballRadius
        // && "Ball Y position is out of top bound"); assert(ballPosition.y <=
        // GetScreenHeight() - ballRadius && "Ball Y position is out of bottom
        // bound");

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // DrawRectangleV(ballPosition, (Vector2){10.f, 10.f}, MAROON);
        DrawCircleV(ball.position, ball.radius, MAROON);
        DrawText("Simple Raylib Example - Bouncing Ball", 10, 10, 20, DARKGRAY);
        DrawFPS(10, 40);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void moveBall(Ball *ball) {
    ball->speed.x += ball->acceleration.x * DELTAT;
    ball->speed.y += ball->acceleration.y * DELTAT;

    ball->position.x += ball->speed.x * DELTAT;
    ball->position.y += ball->speed.y * DELTAT;
}

bool wallColision(Ball *ball) {
    bool colisionOcurred = 0;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    if (ball->position.x - ball->radius < 0 ||
        ball->position.x + ball->radius > screenWidth) {
        ball->speed.x *= -1.0f;
        ball->position.x =
            Clamp(ball->position.x, ball->radius, screenWidth - ball->radius);
        colisionOcurred = true;
    }

    if (ball->position.y - ball->radius < 0 ||
        ball->position.y + ball->radius > screenHeight) {
        ball->speed.y *= -1.0f;
        ball->position.y =
            Clamp(ball->position.y, ball->radius, screenHeight - ball->radius);
        colisionOcurred = true;
    }
    return colisionOcurred;
}

float meterToPixel(float m){
    return m*3779.5275591;
}

float pixelToMeter(float p){
    return p*0.0002645833;
}
