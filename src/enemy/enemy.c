#include "enemy/enemy.h"

#include <raymath.h>
#include "asset/asset_manager.h"
#include "utils/utils.h"
#include "world_state/world_state.h"

void UpdateEnemy(Enemy* enemy, float deltaTime) {
    // rotation
    Vector2 direction = Vector2Normalize(
            Vector2Subtract(
            GetWorldState()->player->position, 
            enemy->position
        )
    );

    enemy->rotation = LerpAngle(
        enemy->rotation, 
        atan2(direction.y, direction.x) * RAD2DEG, 
        ENEMY_ROTATION_SMOOTH_SPEED * deltaTime
    );

    // movement
    enemy->position.x += direction.x * ENEMY_SPEED * deltaTime;
    enemy->position.y += direction.y * ENEMY_SPEED * deltaTime;
}

void DrawEnemy(Enemy* enemy) {
    SpriteSheet sheet = GetSpriteSheet(SS_CHARACTER);

    Rectangle dest = {
        enemy->position.x,
        enemy->position.y,
        sheet.frameSize,
        sheet.frameSize
    };

    Vector2 origin = sheet.origin;

    DrawTexturePro(
        GetTexture(sheet.textureId),
        GetSpriteSheetFrame(sheet, enemy->type, ENEMY_SS_ROW),
        dest,
        origin,
        enemy->rotation,
        WHITE
    );
}