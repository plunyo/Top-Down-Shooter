#include "viewport/viewport.h"
#include <raylib.h>
#include <stdlib.h>

static Viewport* viewport = NULL;

Viewport* LoadViewport() {
    viewport = MemAlloc(sizeof(Viewport));

    viewport->virtualWidth = VIRTUAL_WIDTH;
    viewport->virtualHeight = VIRTUAL_HEIGHT;
 
    viewport->target = LoadRenderTexture(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
    SetTextureFilter(viewport->target.texture, TEXTURE_FILTER_POINT);

    return viewport;
}

void UnloadViewport() {
    UnloadRenderTexture(viewport->target);
    MemFree(viewport);
}

void BeginViewport() {
    BeginTextureMode(viewport->target);
    ClearBackground(BLACK);
}

void EndViewport() {
    EndTextureMode();
}

void DrawViewportToScreen() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    float scaleX = (float)screenWidth / viewport->virtualWidth;
    float scaleY = (float)screenHeight / viewport->virtualHeight;
    float scale = (scaleX < scaleY) ? scaleX : scaleY;

    float drawWidth = viewport->virtualWidth * scale;
    float drawHeight = viewport->virtualHeight * scale;

    float offsetX = (screenWidth - drawWidth) * 0.5f;
    float offsetY = (screenHeight - drawHeight) * 0.5f;

    DrawTexturePro(
        viewport->target.texture,
        (Rectangle){
            0, 0,
            (float)viewport->target.texture.width,
            -(float)viewport->target.texture.height
        },
        (Rectangle){
            offsetX, offsetY,
            drawWidth, drawHeight
        },
        (Vector2){ 0 },
        0.0f,
        WHITE
    );
}

Viewport* GetViewport() {
    return viewport;
}

Vector2 ScreenToViewport(Vector2 point) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    float scaleX = (float)screenWidth / viewport->virtualWidth;
    float scaleY = (float)screenHeight / viewport->virtualHeight;
    float scale = (scaleX < scaleY) ? scaleX : scaleY;

    float drawWidth = viewport->virtualWidth * scale;
    float drawHeight = viewport->virtualHeight * scale;

    float offsetX = (screenWidth - drawWidth) * 0.5f;
    float offsetY = (screenHeight - drawHeight) * 0.5f;

    Vector2 result;
    result.x = (point.x - offsetX) / scale;
    result.y = (point.y - offsetY) / scale;

    return result;
}