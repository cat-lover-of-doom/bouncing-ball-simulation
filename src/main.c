#include "raylib.h"
#include <assert.h>

constexpr int INITIAL_SCREEN_WIDTH = 800;
constexpr int INITIAL_SCREEN_HEIGHT = 450;
constexpr int TARGET_FPS = 60;
constexpr double DELTAT = 1./TARGET_FPS;

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
Vector2 normalToCanvas(Vector2 p);
bool wallColision(Ball *ball);

int main(void) {

    InitWindow(INITIAL_SCREEN_WIDTH, INITIAL_SCREEN_HEIGHT, "Simple Raylib Module");

    SetTargetFPS(TARGET_FPS);

    Ball ball = {.position = {.0f, .0f},
                 .speed = {.03f, .03f},
                 .acceleration = {0.0f, -.015f},
                 .radius = .02f};

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_A)) {
            ball.radius *= 2;
        }
        moveBall(&ball);
        if (!wallColision(&ball)) {
        }

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
        DrawCircleV(normalToCanvas(ball.position), ball.radius * INITIAL_SCREEN_HEIGHT,
                    MAROON);
        DrawText("Simple Raylib Example - Bouncing Ball", 10, 10, 20, DARKGRAY);
        DrawFPS(10, 40);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void moveBall(Ball *ball) {
    ball->position.x += ball->speed.x;
    ball->position.y += ball->speed.y;

    ball->speed.x += ball->acceleration.x;
    ball->speed.y += ball->acceleration.y;
};

Vector2 normalToCanvas(Vector2 p) {
    p.y = (1 - p.y) * 0.5 * (int)GetScreenHeight();
    p.x = (1 + p.x) * 0.5 * (int)GetScreenWidth();
    return p;
}

bool wallColision(Ball *ball) {
    bool colisionOcurred = 0;
    if (ball->position.x - ball->radius < -1 ||
        ball->position.x + ball->radius > 1) {
        ball->speed.x *= -1.0f;
        ball->position.x =
            Clamp(ball->position.x, ball->radius - 1, 1 - ball->radius);
        colisionOcurred = true;
    }

    if (ball->position.y - ball->radius < -1 ||
        ball->position.y + ball->radius > 1) {
        ball->speed.y *= -1.0f;
        ball->position.y =
            Clamp(ball->position.y, ball->radius - 1, 1 - ball->radius);
        colisionOcurred = true;
    }
    return colisionOcurred;
}
