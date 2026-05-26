#pragma once

#include "enemy/enemy_manager.h"
#include "player/player.h"

typedef struct WorldState {
    Player* player;
    EnemyManager* enemyManager;
} WorldState;

WorldState* LoadWorldState();
void UnloadWorldState();

WorldState* GetWorldState();

void UpdateWorldState(float deltaTime);
void DrawWorldState();