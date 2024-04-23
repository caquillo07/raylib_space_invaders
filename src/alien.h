//
// Created by Hector Mejia on 4/2/24.
//
#pragma once

#include "utils/common.h"
#include "raylib.h"

constexpr int AlienTypes = 6;

class Alien {
    private:
        struct AlienAnimation {
            Texture2D textures[2];
            int framesCount;
            int currentFrame;
            int frameSpeed; // TODO(hector) - make this frame independent
            int framesCounter;
        };

        static AlienAnimation alienTextures[AlienTypes];
        int scale = 3;
        f32 speed = 50;
        int type = 1;

        static void initTextures();
    public:
        Vector2 position{};
        Vector2 scaledSize{};

        Alien(int type, Vector2 position);
        ~Alien();

        void Update(f32 deltaTime, i32 direction);
        void Draw();
        int GetType() const;
        static void UnloadTextures();
        Rectangle GetRect();
};
