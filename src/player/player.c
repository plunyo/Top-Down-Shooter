#include "player/player.h"

#include <math.h>
#include <raylib.h>
#include <raymath.h>

#include "asset_manager/asset_manager.h"

static void CenterPlayer(Player* player) {
    player->camera.offset.x = GetScreenWidth() / 2.0f;
    player->camera.offset.y = GetScreenHeight() / 2.0f;
}

static float LerpAngle(float current, float target, float t) {
    float diff = fmodf(target - current + 540.0f, 360.0f) - 180.0f;
    return current + diff * t;
}

Player* InitPlayer(Vector2 initialPosition) {
    Player* instance = MemAlloc(sizeof(Player));

    instance->position = Vector2Zero();
    instance->camera = (Camera2D){
        Vector2Zero(),
        Vector2Zero(),
        0.0f,
        1.0f
    };

    CenterPlayer(instance);

    return instance;
}

void UnloadPlayer(Player* player) {
    MemFree(player);
}

void UpdatePlayer(Player* player, float deltaTime) {
    // rotation
    Vector2 lookDirection = Vector2Subtract(player->position, GetScreenToWorld2D(GetMousePosition(), player->camera));
    player->rotation = LerpAngle(
        player->rotation, 
        (atan2(lookDirection.y, lookDirection.x) + PI) * RAD2DEG, 
        PLAYER_ROTATION_SMOOTH_SPEED * deltaTime
    );
    
    // movement
    Vector2 direction = Vector2Zero();

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    direction.y -= 1;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  direction.x -= 1;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  direction.y += 1;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) direction.x += 1;

    direction = Vector2Normalize(direction);

    player->position.x += direction.x * PLAYER_SPEED * deltaTime;
    player->position.y += direction.y * PLAYER_SPEED * deltaTime;

    // camera following
    player->camera.target = player->position;

    if (IsWindowResized()) CenterPlayer(player);
}

void DrawPlayer(Player *player) {
    Texture2D texture = GetTexture(TEX_PLAYER);

    Vector2 size = { texture.width, texture.height };

    Rectangle source = {
        0.0f, 0.0f,
        (float)texture.width, (float)texture.height
    };

    Rectangle dest = {
        player->position.x, player->position.y,
        size.x, size.y
    };

    Vector2 origin = {
        size.x / 2.0f,
        size.y / 2.0f
    };

    DrawTexturePro(
        texture,
        source,
        dest,
        origin,
        player->rotation,
        WHITE
    );
}