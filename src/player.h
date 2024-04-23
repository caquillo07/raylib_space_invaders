//
// Created by Hector Mejia on 4/1/24.
//

#pragma once

#include "utils/common.h"
#include "raylib.h"
#include "laser.h"
#include <vector>

class Player {
    private:
        Vector2 position{};
        f32 scale = 3.f;
        f32 speed = 300.f;
        f32 renderedWidth = 0.f;
        f32 renderedHeight = 0.f;
        f64 lastLaserTime = 0.0;
        Sound laserSound{};

        void centerPlayer();

    public:
        std::vector<Laser> lasers;
        Texture2D image{};

        Player();
        ~Player();

        void Update(f32 deltaTime);
        void Draw();
        void MoveLeft(f32 deltaTime);
        void MoveRight(f32 deltaTime);
        void FireLaser();
        void Reset();
        Rectangle GetRect();
};
