//
// Created by Hector Mejia on 4/1/24.
//

#include "block.h"

Block::Block(Vector2 position) : position(position) {

}

Block::~Block() {

}

void Block::Draw() {
    DrawRectangleV(position, {3, 3}, Color{243, 216, 63, 255});
}

void Block::Update() {

}

Rectangle Block::GetRect() {
    return Rectangle{
        .x = position.x,
        .y = position.y,
        .width = 3,
        .height = 3,
    };
}
