#include <raylib.h>
#include "enemy/enemy.h"
#include "enemy/enemy_manager.h"
#include "viewport/viewport.h"
#include "world_state/world_state.h"
#include "asset/asset_manager.h"

int main(int argc, char* argv[]) {
    InitWindow(1280, 720, "digga mon digga");
    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);

    LoadAssetManager();
    LoadViewport();
    LoadWorldState();

    SpawnEnemy(GetWorldState()->enemyManager, ENEMY_TYPE_MACHINE, (Vector2){ 200.0f, 200.0f });

    while (!WindowShouldClose()) {
        UpdateWorldState(GetFrameTime());

        BeginViewport();
            DrawWorldState();
        EndViewport();

        BeginDrawing();
            ClearBackground(BLACK);

            DrawViewportToScreen();
            //DrawText("Art by sienna aura", 100, 100, 100, RED);
            DrawText(TextFormat("%d", GetFPS()), 10, 10, 25, WHITE);
        EndDrawing();
    }

    UnloadWorldState();
    UnloadViewport();
    UnloadAssetManager();

    CloseWindow();
    return 0;
}