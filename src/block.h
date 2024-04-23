//
// Created by Hector Mejia on 4/1/24.
//
#pragma once

#include "utils/common.h"
#include "raylib.h"

class Block {
    private:
        Vector2 position{};

    public:
        Block(Vector2 position);
        ~Block();

        void Update();
        void Draw();
        Rectangle GetRect();
};
