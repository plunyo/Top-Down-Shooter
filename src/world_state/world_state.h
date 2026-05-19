#pragma once

#include "player/player.h"

typedef struct WorldState {
    Player* player;
} WorldState;

WorldState* InitWorldState();
void        UnloadWorldState(WorldState* worldState);

void UpdateWorldState(WorldState* worldState, float deltaTime);
void DrawWorldState(WorldState* worldState);