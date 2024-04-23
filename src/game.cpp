//
// Created by Hector Mejia on 4/1/24.
//

#include "game.h"
#include <fstream>

bool Game::debug = false;

Game::Game() {
    this->initGame();
    this->highestScore = this->loadHighScoreFromFile(); // load it once
    this->monogramFont = LoadFontEx("assets/fonts/monogram.ttf", 64, nil, 0);
    this->loadSounds();
    PlayMusicStream(this->music);
}

Game::~Game() {
    this->obstacles.clear();
    this->aliens.clear();
    this->player.lasers.clear();
    Alien::UnloadTextures();
    UnloadFont(this->monogramFont);
    UnloadMusicStream(this->music);
    UnloadSound(this->explosionSound);
}

void Game::Update(f32 deltaTime) {
    UpdateMusicStream(this->music);

    if (!this->isRunning) {
        if (IsKeyPressed(KEY_ENTER)) {
            this->resetGame();
            this->initGame();
        }
        return;
    }
    this->player.Update(deltaTime);

    f64 currentTime = GetTime();
    if (currentTime - timeLastMysteryShipSpawn > mysteryShipSpawnInterval) {
        mysteryShip.Spawn();
        timeLastMysteryShipSpawn = GetTime();
        mysteryShipSpawnInterval = f32(GetRandomValue(10, 20));
    }

    for (auto& laser: this->player.lasers) {
        laser.Update(deltaTime);
    }

    // MoveAliens
    for (auto& alien: this->aliens) {
        if (alien.position.x + alien.scaledSize.x > f32(GetScreenWidth()) - 25) {
            this->aliensDirection = -1;
            moveDownAliens(4);
        }
        if (alien.position.x < 25) {
            aliensDirection = 1;
            moveDownAliens(4);
        }
        alien.Update(deltaTime, aliensDirection);
    }

    alienShootLaser(-200);
    for (auto& laser: this->alienLasers) {
        laser.Update(deltaTime);
    }
    deleteInactiveLasers();
    mysteryShip.Update(deltaTime);

    checkCollisions();
}

void Game::Draw() {
    drawUI();


    this->player.Draw();

    for (auto& laser: this->player.lasers) {
        laser.Draw();
    }

    for (auto& obstacle: this->obstacles) {
        obstacle.Draw();
    }

    for (auto& alien: this->aliens) {
        alien.Draw();
    }

    for (auto& laser: this->alienLasers) {
        laser.Draw();
    }

    mysteryShip.Draw();
}

void Game::drawUI() const {
    const Color gray = Color{29, 29, 27, 255};
    const Color yellow = Color{243, 216, 63, 255};

    // UI
    ClearBackground(gray);
    DrawRectangleRoundedLines(
        Rectangle{
            .x = 10,
            .y = 10,
            .width = 780,
            .height = 780
        },
        0.18f,
        20,
        2,
        yellow
    );

    DrawLineEx(
        Vector2{25, 730},
        Vector2{775, 730},
        3,
        yellow
    );

    std::string rightMostText = "LEVEL 01";
    if (!this->isRunning) {
        rightMostText = "GAME OVER";
    }
    DrawTextEx(monogramFont, rightMostText.c_str(), Vector2{570, 740}, 34, 2, yellow);

    std::string scoreText = fmt::format("SCORE: {:05}", this->score);
    DrawTextEx(monogramFont, scoreText.c_str(), Vector2{50, 15}, 34, 2, yellow);

    std::string highScoreText = fmt::format("HI-SCORE: {:05}", this->highestScore);
    DrawTextEx(monogramFont, highScoreText.c_str(), Vector2{480, 15}, 34, 2, yellow);

    // Player lives
    f32 x = 50;
    for (int i = 0; i < this->playerLives; i++) {
        DrawTextureEx(
            this->player.image,
            Vector2{x, 745},
            0,
            2,
            WHITE
        );
        x += 50;
    }
}

void Game::Close() {
}

void Game::HandleInput() {
    if (!this->isRunning) {
        return;
    }
    f32 deltaTime = GetFrameTime();
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        this->player.MoveLeft(deltaTime);
    } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        this->player.MoveRight(deltaTime);
    }
    if (IsKeyDown(KEY_SPACE)) {
        this->player.FireLaser();
    }

    if (IsKeyPressed(KEY_F1)) {
        Game::debug = !Game::debug;
    }
}

void Game::deleteInactiveLasers() {
    // barffff
    for (auto it = this->player.lasers.begin(); it != this->player.lasers.end();) {
        if (!it->isActive) {
            it = this->player.lasers.erase(it);
        } else {
            it++;
        }
    }

    // barffffffffffffffffff
    for (auto it = this->alienLasers.begin(); it != this->alienLasers.end();) {
        if (!it->isActive) {
            it = this->alienLasers.erase(it);
        } else {
            it++;
        }
    }
}

std::vector<Obstacle> Game::createObstacles() {
    i32 numObstacles = 4;
    usize obstacleWidth = Obstacle::grid[0].size() * 3;
    f32 spaceBetween = (f32(GetScreenWidth()) - f32(numObstacles * obstacleWidth)) / 5;

    for (i32 i = 0; i < numObstacles; i++) {
        f32 offsetX = f32(i + 1) * spaceBetween + f32(i * obstacleWidth);
        Vector2 position = {
            .x = offsetX,
            .y = f32(GetScreenHeight() - 200),
        };
        Obstacle obstacle(position);
        this->obstacles.push_back(obstacle);
    }

    return this->obstacles;
}

std::vector<Alien> Game::createAliens() {
    constexpr i32 xCellSize = 55;
    constexpr i32 yCellSize = 35;
    constexpr i32 xOffset = 75;
    constexpr i32 yOffset = 110;
    for (i32 row = 0; row < 5; row++) {
        for (i32 colum = 0; colum < 11; colum++) {

            Vector2 position = {
                .x = static_cast<float>(colum * xCellSize + xOffset),
                .y = static_cast<float>(row * yCellSize + yOffset),
            };
            this->aliens.push_back(Alien(row + 1 % (AlienTypes), position));
        }
    }

    return this->aliens;
}

void Game::moveDownAliens(f32 distance) {
    for (auto& alien: this->aliens) {
        alien.position.y += distance;
    }
}

void Game::alienShootLaser(f32 laserSpeed) {
    f64 currentTime = GetTime();
    if (aliens.empty() || currentTime - this->timeLastAlienFired < alienShootInterval) {
        return;
    }

    int randomIndex = GetRandomValue(0, i32(this->aliens.size() - 1));
    Alien& alien = this->aliens[randomIndex];
    Vector2 position = {
        .x = alien.position.x + alien.scaledSize.x / 2,
        .y = alien.position.y + alien.scaledSize.y,
    };
    Laser laser(position, i32(laserSpeed));
    this->alienLasers.push_back(laser);
    this->timeLastAlienFired = currentTime;
}

void Game::checkCollisions() {
    // player lasers
    for (auto& laser: player.lasers) {
        auto alienIt = aliens.begin();
        while (alienIt != aliens.end()) {
            if (CheckCollisionRecs(alienIt->GetRect(), laser.GetRect())) {
                PlaySound(this->explosionSound);
                if (alienIt->GetType() == 1) {
                    this->addScore(100);
                } else if (alienIt->GetType() == 2) {
                    this->addScore(200);
                } else if (alienIt->GetType() == 3) {
                    this->addScore(300);
                } else if (alienIt->GetType() == 4) {
                    this->addScore(400);
                } else if (alienIt->GetType() == 5) {
                    this->addScore(500);
                } else if (alienIt->GetType() == 6) {
                    this->addScore(600);
                }

                alienIt = aliens.erase(alienIt);
                laser.isActive = false;
                continue;
            }
            alienIt++;
        }
        // obstacles
        for (auto& obstacle: obstacles) {
            auto obstacleIt = obstacle.blocks.begin();
            while (obstacleIt != obstacle.blocks.end()) {
                if (CheckCollisionRecs(obstacleIt->GetRect(), laser.GetRect())) {
                    obstacleIt = obstacle.blocks.erase(obstacleIt);
                    laser.isActive = false;
                    continue;
                }
                obstacleIt++;
            }
        }

        if (CheckCollisionRecs(mysteryShip.GetRect(), laser.GetRect())) {
            mysteryShip.alive = false;
            laser.isActive = false;
            addScore(500);
        }
    }

    // alien lasers
    for (auto& laser: alienLasers) {
        if (CheckCollisionRecs(laser.GetRect(), player.GetRect())) {
            laser.isActive = false;
            this->playerLives--;
            if (this->playerLives <= 0) {
                gameOver();
            }
        }
        for (auto& obstacle: obstacles) {
            auto obstacleIt = obstacle.blocks.begin();
            while (obstacleIt != obstacle.blocks.end()) {
                if (CheckCollisionRecs(obstacleIt->GetRect(), laser.GetRect())) {
                    obstacleIt = obstacle.blocks.erase(obstacleIt);
                    laser.isActive = false;
                    continue;
                }
                obstacleIt++;
            }
        }
    }

    // alien collision with obstacles
    for (auto& alien: aliens) {
        for (auto& obstacle: obstacles) {
            auto obstacleIt = obstacle.blocks.begin();
            while (obstacleIt != obstacle.blocks.end()) {
                if (CheckCollisionRecs(obstacleIt->GetRect(), alien.GetRect())) {
                    obstacleIt = obstacle.blocks.erase(obstacleIt);
                    continue;
                }
                obstacleIt++;
            }
        }
        if (CheckCollisionRecs(alien.GetRect(), player.GetRect())) {
            gameOver();
        }
    }
}

void Game::addScore(int s) {
    this->score += s;
    if (this->score > this->highestScore) {
        this->highestScore = this->score;
    }
}

void Game::gameOver() {
    this->isRunning = false;
    saveHighScoreToFile();
}

void Game::resetGame() {
    this->player.Reset();
    this->aliens.clear();
    this->alienLasers.clear();
    this->obstacles.clear();
}

void Game::initGame() {
    this->score = 0;
    this->obstacles = createObstacles();
    this->aliens = createAliens();
    this->aliensDirection = 1;
    this->timeLastAlienFired = GetTime();
    this->timeLastMysteryShipSpawn = 0;
    this->mysteryShipSpawnInterval = f32(GetRandomValue(10, 20));
    this->playerLives = 3;
    this->isRunning = true;
}

void Game::saveHighScoreToFile() const {
    #if defined(__unix__) || defined(__unix) || defined(_WIN64) || (defined(__APPLE__) && defined(__MACH__))
    std::ofstream highScoreFile("highscore.txt");
    if (!highScoreFile.is_open()) {
        fmt::print(stderr, "Failed to open highscore.txt for writing\n");
        return;
    }
    highScoreFile << this->highestScore;
    highScoreFile.close();
    #else
    fmt::print(stderr, "Failed to save highscore to file\n");
    return;
    #endif
}

int Game::loadHighScoreFromFile() const {
    #if defined(__unix__) || defined(__unix) || defined(_WIN64) || (defined(__APPLE__) && defined(__MACH__))

    std::ifstream highScoreFile("highscore.txt");
    if (!highScoreFile.is_open()) {
        fmt::print(stderr, "Failed to open highscore.txt for reading\n");
        return 0;
    }
    int highScore = 0;
    highScoreFile >> highScore;
    highScoreFile.close();
    return highScore;

    #else
    fmt::print(stderr, "Failed to load highscore from file\n");
    return 0;
    #endif
}

void Game::loadSounds() {
    this->music = LoadMusicStream("assets/sounds/music.ogg");
    this->explosionSound = LoadSound("assets/sounds/explosion.ogg");
}
