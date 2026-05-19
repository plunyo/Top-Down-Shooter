#pragma once

#include <raylib.h>

typedef enum {
    TEX_CHARACTER_SPRITESHEET,

    TEX_COUNT
} TextureID;

typedef enum {
    SS_CHARACTER,

    SS_COUNT
} SpriteSheetID;

typedef enum {
    SND_COUNT
} SoundID;

typedef struct SpriteSheet {
    TextureID textureId;
    int frameSize;
    Vector2 origin;
} SpriteSheet;

typedef struct AssetManager {
    Texture2D textures[TEX_COUNT];
    SpriteSheet spriteSheets[SS_COUNT];
    Sound sounds[SND_COUNT];
} AssetManager;

void LoadAssetManager(void);
void UnloadAssetManager(void);

void RegisterTexture(TextureID id, const char* path);

void RegisterSpriteSheet(SpriteSheetID id, TextureID textureId, int frameSize, Vector2 origin);

Texture2D GetTexture(TextureID id);
SpriteSheet GetSpriteSheet(SpriteSheetID id);
Sound GetSound(SoundID id);

Rectangle GetSpriteSheetFrame(SpriteSheet sheet, int frameX, int frameY);