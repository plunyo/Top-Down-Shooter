#include <raylib.h>
#include "world_state/world_state.h"
#include "asset_manager/asset_manager.h"

int main(int argc, char* argv[]) {
    InitWindow(960, 540, "digga mon digga");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    LoadAssetManager();

    WorldState* worldState = InitWorldState();

    while (!WindowShouldClose()) {
        UpdateWorldState(worldState, GetFrameTime());

        BeginDrawing();
            ClearBackground(DARKGREEN);

            DrawWorldState(worldState);

            DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadWorldState(worldState);
    UnloadAssetManager();

    CloseWindow();
    return 0;
}