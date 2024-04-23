//
// Created by Hector Mejia on 4/1/24.
//

#include "laser.h"

Laser::Laser(Vector2 position, int speed) : position(position), speed(speed) {
    this->size = {5, 20};
    this->color = Color{243, 216, 63, 255};
}

Laser::~Laser() {

}

void Laser::Update(f32 deltaTime) {
    position.y -= speed * deltaTime;
    if (isActive && (position.y < 25 || position.y > f32(GetScreenHeight()) - 100)) {
        isActive = false;
    }

}

void Laser::Draw() {
    if (!isActive) {
        return;
    }
    DrawRectangleV(position, size, color);
}

Rectangle Laser::GetRect() {
    return Rectangle{
        .x = position.x,
        .y = position.y,
        .width = size.x,
        .height = size.y,
    };
}

