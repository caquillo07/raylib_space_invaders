//
// Created by Hector Mejia on 4/2/24.
//

#include "alien.h"
#include "game.h"
#include <fmt/core.h>

Alien::AlienAnimation Alien::alienTextures[AlienTypes] = {};

Alien::Alien(int type, Vector2 position) : type(type), position(position) {
    if (Alien::alienTextures[0].textures[0].id == 0) {
        Alien::initTextures();
    }
    switch (type) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            break;
        default:
            panic(fmt::format("Invalid alien type: {}", type));
            break;
    }
    this->scaledSize = {
        .x = static_cast<float>(Alien::alienTextures[type - 1].textures[0].width * this->scale),
        .y = static_cast<float>(Alien::alienTextures[type - 1].textures[0].height * this->scale),
    };
}

Alien::~Alien() {

}

void Alien::Update(f32 deltaTime, i32 direction) {
    i32 textureID = this->type - 1;
    Alien::alienTextures[textureID].currentFrame =
        (Alien::alienTextures[textureID].framesCounter / Alien::alienTextures[textureID].frameSpeed) %
        Alien::alienTextures[textureID].framesCount;
    Alien::alienTextures[textureID].framesCounter++;

    this->position.x += float(direction) * this->speed * deltaTime;
}

int Alien::GetType() const {
    return this->type;
}

void Alien::Draw() {
    i32 textureID = this->type - 1;
    auto image = Alien::alienTextures[textureID].textures[Alien::alienTextures[textureID].currentFrame];

    DrawTextureEx(image, this->position, 0, float(this->scale), WHITE);
    if (Game::debug) {
        DrawRectangleLinesEx(this->GetRect(), 2.f, RED);
    }
}

void Alien::initTextures() {
    Alien::alienTextures[0] = {
        .textures = {
            LoadTexture("assets/sprites/alien_1_anim_0.png"),
            LoadTexture("assets/sprites/alien_1_anim_1.png"),
        },
        .framesCount = 2,
        .currentFrame = 0,
        .frameSpeed = FPS * 3,
        .framesCounter = 0,
    };
    Alien::alienTextures[1] = {
        .textures = {
            LoadTexture("assets/sprites/alien_2_anim_0.png"),
            LoadTexture("assets/sprites/alien_2_anim_1.png"),
        },
        .framesCount = 2,
        .currentFrame = 0,
        .frameSpeed = FPS * 3,
        .framesCounter = 0,
    };
    Alien::alienTextures[2] = {
        .textures = {
            LoadTexture("assets/sprites/alien_3_anim_0.png"),
            LoadTexture("assets/sprites/alien_3_anim_1.png"),
        },
        .framesCount = 2,
        .currentFrame = 0,
        .frameSpeed = FPS * 3,
        .framesCounter = 0,
    };
    Alien::alienTextures[3] = {
        .textures = {
            LoadTexture("assets/sprites/alien_4_anim_0.png"),
            LoadTexture("assets/sprites/alien_4_anim_1.png"),
        },
        .framesCount = 2,
        .currentFrame = 0,
        .frameSpeed = FPS * 3,
        .framesCounter = 0,
    };
    Alien::alienTextures[4] = {
        .textures = {
            LoadTexture("assets/sprites/alien_5_anim_0.png"),
            LoadTexture("assets/sprites/alien_5_anim_1.png"),
        },
        .framesCount = 2,
        .currentFrame = 0,
        .frameSpeed = FPS * 3,
        .framesCounter = 0,
    };
    Alien::alienTextures[5] = {
        .textures = {
            LoadTexture("assets/sprites/alien_bonus.png"),
        },
        .framesCount = 1,
        .currentFrame = 0,
        .frameSpeed = FPS * 3,
        .framesCounter = 0,
    };
}

void Alien::UnloadTextures() {
    for (auto& alienTexture : Alien::alienTextures) {
        for (auto& texture : alienTexture.textures) {
            UnloadTexture(texture);
        }
    }
}

Rectangle Alien::GetRect() {
    return Rectangle{
        .x = position.x,
        .y = position.y,
        .width = scaledSize.x,
        .height = scaledSize.y,
    };
}

