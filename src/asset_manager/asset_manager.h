#pragma once

#include "raylib.h"

typedef enum {
    TEX_PLAYER,
    TEX_ENEMY,

    TEX_COUNT,
} TextureID;

typedef enum {
    SND_COUNT,
} SoundID;

typedef struct AssetManager {
    Texture2D textures[TEX_COUNT];
    Sound     sounds[SND_COUNT];
} AssetManager;

void LoadAssetManager();
void UnloadAssetManager();

void RegisterTexture(TextureID id, const char* path);
void RegisterSound(SoundID id, const char* path);

Texture2D GetTexture(TextureID id);
Sound GetSound(SoundID id);
