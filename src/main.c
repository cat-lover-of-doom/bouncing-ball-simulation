//==============================================================================
// Raylearner - Physics Simulation with Raylib
//==============================================================================
// A real-time 2D physics simulation demonstrating:
// - Fixed timestep integration using the accumulator pattern
// - Elastic collisions with energy loss (coefficient of restitution)
// - Gravity simulation with proper unit conversions
// - Interactive controls for experimentation
//
// Physics approach:
// - Uses a fixed simulation timestep (SIM_DT) for deterministic physics
// - Accumulates frame time and runs multiple physics steps per frame if needed
// - Implements semi-implicit Euler integration (velocity then position)
// - Screen coordinates: origin at top-left, Y increases downward
//==============================================================================

#include "raylib.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

constexpr int INITIAL_SCREEN_WIDTH = 800;
constexpr int INITIAL_SCREEN_HEIGHT = 450;

constexpr double FRAMETIME_MAX = 0.25;

// Fixed simulation timestep: 1/12000 seconds (~83 microseconds)
constexpr double SIM_DT = 1.0 / 12000.0;

// Conversion factor: 1 meter = 3779.5275591 pixels (96 DPI)
// This assumes 96 DPI screen resolution: 1 inch = 96 pixels, 1 meter = 39.3701
// inches
constexpr double METERS_TO_PIXELS_FACTOR = 3779.5275591;

constexpr double RESTITUTION = 0.92;
constexpr double GRAVITY_ACCELERATION = 9.8;

typedef struct Ball {
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    double radius;
} Ball;

static double clamp(double value, double min, double max);
static void ball_update_physics(Ball *ball);
static bool ball_handle_wall_collision(Ball *ball);
static void ball_reset(Ball *ball);

int main(void) {

    InitWindow(INITIAL_SCREEN_WIDTH, INITIAL_SCREEN_HEIGHT,
               "Raylearner - Physics Simulation");
    SetTargetFPS(120);

    Ball ball = {
        .position = {400.0, 225.0},
        .velocity = {200.0, 200.0},
        .acceleration = {0.0, GRAVITY_ACCELERATION * METERS_TO_PIXELS_FACTOR},
        .radius = 20.0,
    };

    // Physics accumulator for fixed timestep integration
    // See: https://gafferongames.com/post/fix_your_timestep/
    double sim_time_accumulator = 0.0;

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_A)) {
            ball.radius *= 2.0;
        }
        if (IsKeyPressed(KEY_S)) {
            ball.radius /= 2.0;
            if (ball.radius < 5.0)
                ball.radius = 5.0;
        }
        if (IsKeyPressed(KEY_SPACE)) {
            ball_reset(&ball);
        }

        double frametime = GetFrameTime();

        if (frametime > FRAMETIME_MAX) {
            frametime = FRAMETIME_MAX;
        }

        sim_time_accumulator += frametime;
        while (sim_time_accumulator >= SIM_DT) {
            ball_update_physics(&ball);
            ball_handle_wall_collision(&ball);
            sim_time_accumulator -= SIM_DT;
        }

        assert(ball.position.x >= ball.radius &&
               ball.position.x <= GetScreenWidth() - ball.radius);
        assert(ball.position.y >= ball.radius &&
               ball.position.y <= GetScreenHeight() - ball.radius);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircleV(ball.position, (float)ball.radius, MAROON);

        DrawText("Raylearner Physics Simulation", 10, 10, 20, DARKGRAY);
        DrawFPS(10, 40);

        DrawText(TextFormat("Velocity: (%.1f, %.1f) px/s", ball.velocity.x,
                            ball.velocity.y),
                 10, 70, 16, DARKGRAY);
        DrawText(TextFormat("Acceleration: (%.1f, %.1f) px/s^2",
                            ball.acceleration.x, ball.acceleration.y),
                 10, 90, 16, DARKGRAY);

        DrawText("Controls:", 10, 120, 16, DARKGRAY);
        DrawText("  A - Increase ball size", 10, 140, 14, GRAY);
        DrawText("  S - Decrease ball size", 10, 160, 14, GRAY);
        DrawText("  SPACE - Reset ball", 10, 180, 14, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

static double clamp(double value, double min, double max) {
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

static void ball_update_physics(Ball *ball) {
    // Semi-implicit Euler integration (velocity first, then position)
    // This is more stable than explicit Euler for physics simulation
    ball->velocity.x += ball->acceleration.x * SIM_DT;
    ball->velocity.y += ball->acceleration.y * SIM_DT;

    ball->position.x += ball->velocity.x * SIM_DT;
    ball->position.y += ball->velocity.y * SIM_DT;
}

static bool ball_handle_wall_collision(Ball *ball) {
    bool collision_occurred = false;
    const int screen_width = GetScreenWidth();
    const int screen_height = GetScreenHeight();

    if (ball->position.x - ball->radius < 0.0 ||
        ball->position.x + ball->radius > screen_width) {

        ball->velocity.x *= -RESTITUTION;

        ball->position.x =
            clamp(ball->position.x, ball->radius, screen_width - ball->radius);

        collision_occurred = true;
    }

    if (ball->position.y - ball->radius < 0.0 ||
        ball->position.y + ball->radius > screen_height) {

        ball->velocity.y *= -RESTITUTION;

        ball->position.y =
            clamp(ball->position.y, ball->radius, screen_height - ball->radius);

        collision_occurred = true;
    }

    return collision_occurred;
}

static void ball_reset(Ball *ball) {
    ball->position = (Vector2){400.0, 225.0};
    ball->velocity = (Vector2){200.0, 200.0};
    ball->acceleration =
        (Vector2){0.0, GRAVITY_ACCELERATION * METERS_TO_PIXELS_FACTOR};
    ball->radius = 20.0;
}
