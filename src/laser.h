//
// Created by Hector Mejia on 4/1/24.
//
#pragma once

#include "utils/common.h"
#include "raylib.h"

class Laser {
    private:
        Vector2 position;
        int speed;
        Vector2 size = {10, 20};
        Color color = WHITE;

    public:
        bool isActive = true;

        Laser(Vector2 position, int speed);
        ~Laser();

        void Draw();
        void Update(f32 deltaTime);
        Rectangle GetRect();
};
