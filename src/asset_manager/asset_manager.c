#include "asset_manager/asset_manager.h"
#include "raylib.h"

static AssetManager assetManager = { 0 };

void LoadAssetManager() {
    RegisterTexture(TEX_PLAYER, "assets/character/man_blue/man_blue_hold.png");
    RegisterTexture(TEX_ENEMY,  "assets/character/zombie/zombie_hold.png");
}

void UnloadAssetManager() {
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

void RegisterSound(SoundID id, const char* path) {
    assetManager.sounds[id] = LoadSound(path);
}

Texture2D GetTexture(TextureID id) {
    return assetManager.textures[id];
}

Sound GetSound(SoundID id) {
    return assetManager.sounds[id];
}