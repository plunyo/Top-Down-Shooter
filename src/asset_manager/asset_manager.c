#include "asset_manager/asset_manager.h"

static AssetManager assetManager = { 0 };

void LoadAssetManager(void) {
    RegisterTexture(TEX_CHARACTER_SPRITESHEET, "assets/textures/character/character_spritesheet.png");

    RegisterSpriteSheet(
        SS_CHARACTER,
        TEX_CHARACTER_SPRITESHEET,
        64,
        (Vector2){ 15.0f, 32.0f }
    );
}

void UnloadAssetManager(void) {
    for (int i = 0; i < TEX_COUNT; i++) {
        UnloadTexture(assetManager.textures[i]);
    }

    for (int i = 0; i < SND_COUNT; i++) {
        UnloadSound(assetManager.sounds[i]);
    }
}

void RegisterTexture(TextureID id, const char* path) {
    assetManager.textures[id] = LoadTexture(path);
}

void RegisterSpriteSheet(SpriteSheetID id, TextureID textureId, int frameSize, Vector2 origin) {
    assetManager.spriteSheets[id] = (SpriteSheet){
        .textureId = textureId,
        .frameSize = frameSize,
        .origin = origin
    };
}

Texture2D GetTexture(TextureID id) {
    return assetManager.textures[id];
}

SpriteSheet GetSpriteSheet(SpriteSheetID id) {
    return assetManager.spriteSheets[id];
}

Sound GetSound(SoundID id) {
    return assetManager.sounds[id];
}

Rectangle GetSpriteSheetFrame(SpriteSheet sheet, int frameX, int frameY) {
    return (Rectangle){
        frameX * sheet.frameSize,
        frameY * sheet.frameSize,
        sheet.frameSize,
        sheet.frameSize
    };
}