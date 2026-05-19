#pragma once

#include <raylib.h>

#define VIRTUAL_WIDTH 960
#define VIRTUAL_HEIGHT 540

typedef struct Viewport {
    int virtualWidth;
    int virtualHeight;

    RenderTexture2D target;
} Viewport;

Viewport* LoadViewport();
void UnloadViewport();

void BeginViewport();
void EndViewport();

void DrawViewportToScreen();

Viewport* GetViewport();
Vector2 ScreenToViewport(Vector2 point);