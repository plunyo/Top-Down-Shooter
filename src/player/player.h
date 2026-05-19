#pragma once

#include <raylib.h>

#define PLAYER_SPEED 300.0f
#define PLAYER_SIZE  100.0f
#define PLAYER_ROTATION_SMOOTH_SPEED 10.0f

typedef struct Player {
    Vector2 position;
    float rotation;

    Camera2D camera;
} Player;

Player* InitPlayer(Vector2 initialPosition);
void    UnloadPlayer(Player* player);

void UpdatePlayer(Player* player, float deltaTime);
void DrawPlayer(Player* player);