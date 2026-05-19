#include "world_state/world_state.h"
#include "player/player.h"
#include "raymath.h"
#include <raylib.h>

WorldState* InitWorldState() {
    WorldState* instance = MemAlloc(sizeof(WorldState));

    instance->player = InitPlayer(Vector2Zero());

    return instance;
}

void UnloadWorldState(WorldState* worldState) {
    UnloadPlayer(worldState->player);
    MemFree(worldState);
}

void UpdateWorldState(WorldState* worldState, float deltaTime) {
    UpdatePlayer(worldState->player, deltaTime);
}

void DrawWorldState(WorldState* worldState) {
    BeginMode2D(worldState->player->camera);
        DrawRectangle(0, 0, 100, 100, RED);
        
        DrawPlayer(worldState->player);
    EndMode2D();
}