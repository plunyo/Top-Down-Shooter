#include <raylib.h>
#include "viewport/viewport.h"
#include "world_state/world_state.h"
#include "asset_manager/asset_manager.h"

int main(int argc, char* argv[]) {
    InitWindow(1920, 1080, "digga mon digga");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    LoadAssetManager();
    LoadViewport();

    WorldState* worldState = InitWorldState();

    while (!WindowShouldClose()) {
        UpdateWorldState(worldState, GetFrameTime());

        BeginViewport();
            DrawWorldState(worldState);
        EndViewport();

        BeginDrawing();
            ClearBackground(BLACK);

            DrawViewportToScreen();
            //DrawText("Art by sienna aura", 100, 100, 100, RED);
            DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadWorldState(worldState);
    UnloadViewport();
    UnloadAssetManager();

    CloseWindow();
    return 0;
}