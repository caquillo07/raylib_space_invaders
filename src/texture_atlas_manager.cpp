//
// Created by Hector Mejia on 4/1/24.
//

#include "utils/common.h"
#include "texture_atlas_manager.h"
#include "texture_atlas.h"
#include <fmt/core.h>

TextureAtlasManager::TextureAtlasManager() {
    this->atlases.emplace_back(
        TextureAtlas(DefaultAtlasName, "assets/atlas.png", "assets/atlas.json")
    );
}

TextureAtlasManager::~TextureAtlasManager() {
    this->atlases.clear();
}

TextureAtlas& TextureAtlasManager::GetAtlas(const string& name) {
    for (auto& atlas: this->atlases) {
        if (atlas.Name == name) {
            return atlas;
        }
    }

    panic(fmt::format("Atlas with name \"{}\" not found", name));
    return this->atlases[0];
}

const Sprite& getSprite(const TextureAtlas& atlas, const string& spriteName) {
    for (auto& sprite: atlas.sprites) {
        if (sprite.name == spriteName) {
            return sprite;
        }
    }

    panic(
        fmt::format(
            R"(Sprite with name "{}" not found in atlas "{}")",
            spriteName,
            atlas.Name
        ));
    return atlas.sprites[0];
}

const Sprite& TextureAtlasManager::GetSprite(const string& atlasName, const string& spriteName) {
    TextureAtlas& atlas = this->GetAtlas(atlasName);
    return getSprite(atlas, spriteName);
}

const Sprite& TextureAtlasManager::GetSprite(const TextureAtlas& atlas, const string& spriteName) {
    return getSprite(atlas, spriteName);
}
