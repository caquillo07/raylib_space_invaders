//
// Created by Hector Mejia on 4/1/24.
//
#pragma once

#include "block.h"
#include "fmt/core.h"
#include "raylib.h"
#include <vector>

class Obstacle {
    public:
        Vector2 position{};
        std::vector<Block> blocks;
        static std::vector<std::vector<u8>> grid;

        Obstacle(Vector2 position);
        ~Obstacle();

        void Update();
        void Draw();
};
