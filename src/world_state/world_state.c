#include "world_state/world_state.h"
#include "enemy/enemy_manager.h"
#include "player/player.h"
#include "raymath.h"
#include <raylib.h>

static WorldState* worldState;

WorldState* LoadWorldState() {
    worldState = MemAlloc(sizeof(WorldState));

    worldState->player = InitPlayer(Vector2Zero());
    worldState->enemyManager = InitEnemyManager();

    return worldState;
}

WorldState* GetWorldState() {
    return worldState;
}

void UnloadWorldState() {
    UnloadPlayer(worldState->player);
    UnloadEnemyManager(worldState->enemyManager);
    MemFree(worldState);
}

void UpdateWorldState(float deltaTime) {
    UpdateEnemies(worldState->enemyManager, deltaTime);
    UpdatePlayer(worldState->player, deltaTime);
}

void DrawWorldState() {
    BeginMode2D(worldState->player->camera);
        ClearBackground(DARKGREEN);

        DrawRectangle(0, 0, 100, 100, RED);
        DrawEnemies(worldState->enemyManager);
        DrawPlayer(worldState->player);
    EndMode2D();
}