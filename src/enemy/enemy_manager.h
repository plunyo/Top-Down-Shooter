#pragma once

#include "enemy/enemy.h"
#include "raylib.h"

#define MAX_ENEMIES 1024

typedef struct EnemyManager {
    Enemy enemies[MAX_ENEMIES];
} EnemyManager;

EnemyManager* InitEnemyManager();
void UnloadEnemyManager(EnemyManager* enemyManager);

void SpawnEnemy(EnemyManager* enemyManager, EnemyType type, Vector2 position);

void UpdateEnemies(EnemyManager* enemyManager, float deltaTime);
void DrawEnemies(EnemyManager* enemyManager);