//
// Created by Hector Mejia on 4/1/24.
//

#include "player.h"

constexpr f32 padding = 100.f;

Player::Player() {
    this->laserSound = LoadSound("assets/sounds/laser.ogg");
    this->image = LoadTexture("assets/sprites/player.png");
    this->scale = 3.f;
    this->speed = 300.f;
    this->renderedWidth = f32(this->image.width) * this->scale;
    this->renderedHeight = f32(this->image.height) * this->scale;
    centerPlayer();
}

Player::~Player() {
    UnloadTexture(this->image);
    UnloadSound(this->laserSound);
}

void Player::FireLaser() {
    constexpr f64 threshold = 0.35; // in ms
    if (GetTime() - this->lastLaserTime <= threshold) { // in ms
        return;
    }

    Vector2 laserPosition = {
        .x = this->position.x + (this->renderedWidth / 2.f) - 2,
        .y = this->position.y,
    };
    Laser laser(laserPosition, 500);
    this->lasers.push_back(laser);
    this->lastLaserTime = GetTime();
    PlaySound(this->laserSound);
}

void Player::Draw() {
    DrawTextureEx(
        this->image,
        this->position,
        0,
        3,
        WHITE
    );
}

void Player::MoveLeft(f32 deltaTime) {
    position.x -= speed * deltaTime;
    if (position.x <= 25) {
        position.x = 25;
    }
}

void Player::MoveRight(f32 deltaTime) {
    position.x += speed * deltaTime;
    if (position.x >= f32(GetScreenWidth()) - this->renderedWidth - 25) {
        position.x = f32(GetScreenWidth()) - this->renderedWidth - 25;
    }
}

void Player::Update(f32 deltaTime) {
}

Rectangle Player::GetRect() {
    return Rectangle{
        .x = position.x,
        .y = position.y,
        .width = renderedWidth,
        .height = renderedHeight,
    };
}

void Player::Reset() {
    centerPlayer();
    this->lasers.clear();
}

void Player::centerPlayer() {
    this->position = {
        .x = (static_cast<float>(GetScreenWidth()) - this->renderedWidth) / 2.f,
        .y = static_cast<float>(GetScreenHeight()) - this->renderedHeight - padding,
    };
}
