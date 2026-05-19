#pragma once

#include <raylib.h>

#define PLAYER_SPEED 300.0f
#define PLAYER_SIZE  100.0f
#define PLAYER_ROTATION_SMOOTH_SPEED 10.0f

#define SPRITESHEET_FRAME_SIZE 64

#define PLAYER_OFFSET_X 15
#define PLAYER_OFFSET_Y 32

typedef enum PlayerVariant {
    PLAYER_VARIANT_HITMAN,
    PLAYER_VARIANT_MAN_BLUE,
    PLAYER_VARIANT_MAN_BROWN,
    PLAYER_VARIANT_ROBOT,
    PLAYER_VARIANT_SOLDIER,
    PLAYER_VARIANT_WOMAN_GREEN,
    PLAYER_VARIANT_ZOMBIE,
    PLAYER_VARIANT_SURVIVOR,
} PlayerVariant;

typedef enum PlayerAction {
    PLAYER_ACTION_PISTOL,
    PLAYER_ACTION_HOLD,
    PLAYER_ACTION_MACHINE,
    PLAYER_ACTION_RELOAD,
    PLAYER_ACTION_SILENCER,
    PLAYER_ACTION_STAND,
} PlayerAction;

typedef struct Player {
    Vector2 position;
    float rotation;

    PlayerVariant variant;
    PlayerAction  action;

    Camera2D camera;
} Player;

Player* InitPlayer(Vector2 initialPosition);
void    UnloadPlayer(Player* player);

void UpdatePlayer(Player* player, float deltaTime);
void DrawPlayer(Player* player);