#include "player/player.h"

#include <math.h>
#include <raylib.h>
#include <raymath.h>

#include "asset/asset_manager.h"
#include "viewport/viewport.h"
#include "utils/utils.h"

static void CenterPlayer(Player* player) {
    player->camera.offset.x = VIRTUAL_WIDTH / 2.0f;
    player->camera.offset.y = VIRTUAL_HEIGHT / 2.0f;
}

Player* InitPlayer(Vector2 initialPosition) {
    Player* instance = MemAlloc(sizeof(Player));

    instance->position = Vector2Zero();
    instance->velocity = Vector2Zero();
    instance->rotation = 0.0f;

    instance->variant = PLAYER_VARIANT_SOLDIER;
    instance->action = PLAYER_ACTION_MACHINE;

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
    // IGNORE THIS HORROR, TEMPORARY CODE....
    if (IsKeyDown(KEY_LEFT_BRACKET)) {
        if (IsKeyPressed(KEY_ONE))   player->variant = PLAYER_VARIANT_SOLDIER;
        if (IsKeyPressed(KEY_TWO))   player->variant = PLAYER_VARIANT_ROBOT;
        if (IsKeyPressed(KEY_THREE)) player->variant = PLAYER_VARIANT_HITMAN;
        if (IsKeyPressed(KEY_FOUR))  player->variant = PLAYER_VARIANT_MAN_BLUE;
        if (IsKeyPressed(KEY_FIVE))  player->variant = PLAYER_VARIANT_MAN_BROWN;
        if (IsKeyPressed(KEY_SIX))   player->variant = PLAYER_VARIANT_SURVIVOR;
        if (IsKeyPressed(KEY_SEVEN)) player->variant = PLAYER_VARIANT_WOMAN_GREEN;
        if (IsKeyPressed(KEY_EIGHT)) player->variant = PLAYER_VARIANT_ZOMBIE;
    } else if (IsKeyDown(KEY_RIGHT_BRACKET)) {
        if (IsKeyPressed(KEY_ONE))   player->action = PLAYER_ACTION_HOLD;
        if (IsKeyPressed(KEY_TWO))   player->action = PLAYER_ACTION_MACHINE;
        if (IsKeyPressed(KEY_THREE)) player->action = PLAYER_ACTION_PISTOL;
        if (IsKeyPressed(KEY_FOUR))  player->action = PLAYER_ACTION_RELOAD;
        if (IsKeyPressed(KEY_FIVE))  player->action = PLAYER_ACTION_SILENCER;
        if (IsKeyPressed(KEY_SIX))   player->action = PLAYER_ACTION_STAND;
    }

    // rotation
    Vector2 lookDirection = Vector2Subtract(
        GetScreenToWorld2D(
            ScreenToViewport(GetMousePosition()), 
            player->camera
        ), 
        player->position
    );

    player->rotation = LerpAngle(
        player->rotation, 
        atan2(lookDirection.y, lookDirection.x) * RAD2DEG, 
        PLAYER_ROTATION_SMOOTH_SPEED * deltaTime
    );
    
    // movement
    Vector2 direction = Vector2Zero();

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    direction.y -= 1;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  direction.x -= 1;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  direction.y += 1;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) direction.x += 1;

    if (Vector2Length(direction) > 0.0f)
        direction = Vector2Normalize(direction);

    // accelerate toward movement direction
    Vector2 desiredVelocity = Vector2Scale(direction, PLAYER_SPEED);

    player->velocity = Vector2Lerp(
        player->velocity,
        desiredVelocity,
        PLAYER_ACCEL * deltaTime
    );

    if (Vector2Length(direction) == 0.0f) {
        player->velocity = Vector2Lerp(
            player->velocity,
            Vector2Zero(),
            PLAYER_DECEL * deltaTime
        );
    }

    // apply velocity
    player->position = Vector2Add(
        player->position,
        Vector2Scale(player->velocity, deltaTime)
    );

    // camera following
    player->camera.target = player->position;

    if (IsWindowResized()) CenterPlayer(player);
}

void DrawPlayer(Player *player) {
    SpriteSheet sheet = GetSpriteSheet(SS_CHARACTER);

    Rectangle dest = {
        player->position.x,
        player->position.y,
        sheet.frameSize,
        sheet.frameSize
    };

    Vector2 origin = sheet.origin;

    DrawTexturePro(
        GetTexture(sheet.textureId),
        GetSpriteSheetFrame(sheet, player->action, player->variant),
        dest,
        origin,
        player->rotation,
        WHITE
    );
}