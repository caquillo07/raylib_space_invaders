//
// Created by Hector Mejia on 4/16/24.
//

#include "mystery_ship.h"

MysteryShip::MysteryShip() {
    this->image = LoadTexture("assets/sprites/alien_bonus.png");
    this->alive = false;
    this->scale = 3.f;
    this->speed = 100;
    this->renderedWidth = f32(this->image.width) * this->scale;
    this->renderedHeight = f32(this->image.height) * this->scale;
    this->position = {
        .x = f32(GetScreenWidth()) - this->renderedWidth,
        .y = 50,
    };
}

MysteryShip::~MysteryShip() {
    UnloadTexture(this->image);
}

void MysteryShip::Update(f32 deltaTime) {
    if (!alive) {
        return;
    }
    position.x += direction * speed * deltaTime;
    if (position.x > f32(GetScreenWidth()) - this->renderedWidth - 25 || position.x < 25) {
        alive = false;
    }
}

void MysteryShip::Draw() {
    if (!alive) {
        return;
    }
    DrawTextureEx(this->image, this->position, 0, this->scale, WHITE);
}

void MysteryShip::Spawn() {
    position.y = 70;
    if (GetRandomValue(0,1) == 0) {
        position.x = 25;
        direction = 1;
    } else {
        position.x = f32(GetScreenWidth()) - this->renderedWidth - 25;
        direction = -1;
    }
    this->alive = true;
}

Rectangle MysteryShip::GetRect() {
    if (!alive) {
        return Rectangle {
            .x = position.x,
            .y = position.y,
            .width = 0,
            .height = 0,
        };
    }
    return Rectangle{
        .x = position.x,
        .y = position.y,
        .width = renderedWidth,
        .height = renderedHeight,
    };
}
