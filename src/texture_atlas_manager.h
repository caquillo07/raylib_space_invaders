//
// Created by Hector Mejia on 4/1/24.
//
#pragma once

#include "utils/common.h"
#include <vector>

class TextureAtlas;
struct Sprite;

using namespace std;

constexpr const char *DefaultAtlasName = "main_atlas";

class TextureAtlasManager {
    private:
        std::vector<TextureAtlas> atlases{};

    public:
        TextureAtlasManager();
        ~TextureAtlasManager();

        TextureAtlas& GetAtlas(const string& name);
        const Sprite& GetSprite(const string& atlasName, const string& spriteName);
        const Sprite& GetSprite(const TextureAtlas& atlas, const string& spriteName);
};
