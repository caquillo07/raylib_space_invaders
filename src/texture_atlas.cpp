//
// Created by Hector Mejia on 4/1/24.
//

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

#include "texture_atlas.h"
#include "spdlog/spdlog.h"

using json = nlohmann::json;

TextureAtlas::TextureAtlas() {
    panic("TextureAtlas constructor called without parameters");
}

TextureAtlas::TextureAtlas(string name, const char *imagePath, string jsonPath) : Name(name) {
    std::ifstream jsonFile(jsonPath);
    json atlas = json::parse(jsonFile);
    jsonFile.close();

    // get all the sprites from the json file
    auto now = std::chrono::system_clock::now();
    for (auto& sprite: atlas["sprites"]) {
        Sprite s = {
            .name = sprite["nameId"],
            .frame = {
                sprite["position"]["x"],
                sprite["position"]["y"],
                sprite["sourceSize"]["width"],
                sprite["sourceSize"]["height"],
            },
            .origin = {
                sprite["origin"]["x"],
                sprite["origin"]["y"],
            },
        };

        this->sprites.push_back(s);
    }

    this->spriteCount = this->sprites.size();
    this->texture = LoadTexture(imagePath);

    std::chrono::duration<double> elapsedTimeMS = std::chrono::system_clock::now() - now;
    spdlog::info(
        "Loaded atlas \"{}\" with {} sprites in {} ms",
        this->Name,
        this->spriteCount,
        elapsedTimeMS.count() * 1000
    );
}

TextureAtlas::~TextureAtlas() {
    this->sprites.clear();
    UnloadTexture(this->texture);
}

