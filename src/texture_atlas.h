//
// Created by Hector Mejia on 4/1/24.
//
#pragma once

#include "utils/common.h"
#include "raylib.h"

using namespace std;

struct Sprite {
    string name;
    Rectangle frame;
    Vector2 origin;
};

class TextureAtlas {
    public:
        u32 spriteCount = 0;
        Texture texture{};
        string Name;
        vector<Sprite> sprites;

        TextureAtlas();
        TextureAtlas(string name, const char *imagePath, string jsonPath);
        ~TextureAtlas();
};
