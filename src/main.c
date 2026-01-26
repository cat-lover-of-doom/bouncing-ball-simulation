#include "raylib.h"
#include <assert.h>

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 450;

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

int main(void) {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simple Raylib Module");

  SetTargetFPS(60);

  Ball ball = {.position = {(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2},
               .speed = {6.0f, 60.0f},
               .radius = 10.0f};

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_A)) {
      ball.radius *= 2;
    }
    ball.position.x += ball.speed.x;
    ball.position.y += ball.speed.y;

    if (ball.position.x - ball.radius < 0 ||
        ball.position.x + ball.radius > GetScreenWidth()) {
      ball.speed.x *= -1.0f;
      ball.position.x =
          Clamp(ball.position.x, ball.radius, GetScreenWidth() - ball.radius);
    }

    if (ball.position.y - ball.radius < 0 ||
        ball.position.y + ball.radius > GetScreenHeight()) {
      ball.speed.y *= -1.0f;
      ball.position.y =
          Clamp(ball.position.y, ball.radius, GetScreenHeight() - ball.radius);
    }

    // TODO: fix this shit
    // assert(ballPosition.x >= ballRadius && "Ball X position is out of left
    // bound"); assert(ballPosition.x <= GetScreenWidth() - ballRadius && "Ball
    // X position is out of right bound"); assert(ballPosition.y >= ballRadius
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
