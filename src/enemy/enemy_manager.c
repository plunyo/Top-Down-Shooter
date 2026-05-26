#include "enemy/enemy_manager.h"
#include "enemy/enemy.h"
#include "raymath.h"
#include <raylib.h>

EnemyManager* InitEnemyManager() {
    EnemyManager* instance = MemAlloc(sizeof(EnemyManager));

    for (int i = 0; i < MAX_ENEMIES; i++) {
        instance->enemies[i] = (Enemy){
            false,
            Vector2Zero(),
            0.0f
        };
    }

    return instance;
}

void UnloadEnemyManager(EnemyManager* enemyManager) {
    MemFree(enemyManager);
}

void SpawnEnemy(EnemyManager* enemyManager, EnemyType type, Vector2 position) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        Enemy* enemy = &enemyManager->enemies[i];
        if (enemy->active) continue;
        
        // "init" enemy
        enemy->active = true;   
        enemy->type = type;
        enemy->position = position;
    }
}

void UpdateEnemies(EnemyManager* enemyManager, float deltaTime) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        Enemy* enemy = &enemyManager->enemies[i];
        if (!enemy->active) continue;

        UpdateEnemy(enemy, deltaTime);
    }
}

void DrawEnemies(EnemyManager* enemyManager) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        Enemy* enemy = &enemyManager->enemies[i];
        if (!enemy->active) continue;

        DrawEnemy(enemy);
    }
}
