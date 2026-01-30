#include "raylib.h"
#include <assert.h>

constexpr int INITIAL_SCREEN_WIDTH = 800;
constexpr int INITIAL_SCREEN_HEIGHT = 450;
constexpr double FRAMETIME_MAX = .25f;
constexpr double SIM_DT = 1./12000;

typedef struct ball {
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    double radius;
} Ball;

double Clamp(double d, double min, double max) {
    const double t = d < min ? min : d;
    return t > max ? max : t;
}
void moveBall(Ball *ball);
bool wallColision(Ball *ball);
double meterToPixel(double m);
double pixelToMeter(double p);

int main(void) {

    InitWindow(INITIAL_SCREEN_WIDTH, INITIAL_SCREEN_HEIGHT, "BALL");
    SetTargetFPS(120);

    Ball ball = {.position = {400.0f, 225.0f},
                 .velocity = {200.0f, 200.0f},
                 .acceleration = {0.0f, meterToPixel(9.8f)},
                 .radius = 20.0f};

    double simTime = 0.f;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_A)) {
            ball.radius *= 2;
        }
        double frametime = GetFrameTime();
        if (frametime > FRAMETIME_MAX) {
            frametime = FRAMETIME_MAX;
        }
        simTime += frametime;
        while (simTime >= SIM_DT) {
            moveBall(&ball);
            wallColision(&ball);
            simTime-=SIM_DT;
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
        DrawCircleV(ball.position, ball.radius, MAROON);
        DrawText("BALL GO BRRRR", 10, 10, 20, DARKGRAY);
        DrawFPS(10, 40);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void moveBall(Ball *ball) {
    ball->velocity.x += ball->acceleration.x * SIM_DT;
    ball->velocity.y += ball->acceleration.y * SIM_DT;

    ball->position.x += ball->velocity.x * SIM_DT;
    ball->position.y += ball->velocity.y * SIM_DT;
}

bool wallColision(Ball *ball) {
    bool colisionOcurred = 0;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    if (ball->position.x - ball->radius < 0 ||
        ball->position.x + ball->radius > screenWidth) {
        ball->velocity.x *= -1.0f;
        ball->position.x =
            Clamp(ball->position.x, ball->radius, screenWidth - ball->radius);
        colisionOcurred = true;
    }

    if (ball->position.y - ball->radius < 0 ||
        ball->position.y + ball->radius > screenHeight) {
        ball->velocity.y *= -1.0f;
        ball->position.y =
            Clamp(ball->position.y, ball->radius, screenHeight - ball->radius);
        colisionOcurred = true;
    }
    return colisionOcurred;
}

double meterToPixel(double m) { return m * 3779.5275591; }

double pixelToMeter(double p) { return p * 0.0002645833; }
