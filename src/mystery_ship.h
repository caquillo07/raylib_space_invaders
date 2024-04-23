//
// Created by Hector Mejia on 4/16/24.
//
#pragma once

#include "utils/common.h"
#include <raylib.h>

class MysteryShip {
    private:
        Vector2 position{};
        Texture2D image{};
        f32 scale = 3.f;
        f32 renderedWidth = 0.f;
        f32 renderedHeight = 0.f;
        f32 speed = 100;
        f32 direction = 1;

    public:
        bool alive = false;

        MysteryShip();
        ~MysteryShip();
        void Update(f32 deltaTime);
        void Draw();
        void Spawn();
        Rectangle GetRect();
};

