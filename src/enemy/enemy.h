#pragma once

#include <raylib.h>
#include <stdbool.h>

#define ENEMY_SPEED 65.0f
#define ENEMY_SS_ROW 6
#define ENEMY_ROTATION_SMOOTH_SPEED 12.0f

typedef enum EnemyType {
    ENEMY_TYPE_PISTOL,
    ENEMY_TYPE_FIST,
    ENEMY_TYPE_MACHINE,
    ENEMY_TYPE_RELOAD,
    ENEMY_TYPE_SILENCER,
    ENEMY_TYPE_STAND,
} EnemyType;

typedef struct Enemy {
    bool active;
    Vector2 position;
    float rotation;
    EnemyType type;
} Enemy;

void UpdateEnemy(Enemy* enemy, float deltaTime);  
void DrawEnemy(Enemy* enemy);
