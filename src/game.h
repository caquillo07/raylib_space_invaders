//
// Created by Hector Mejia on 4/1/24.
//
#pragma once

#include "player.h"
#include "laser.h"
#include "obstacle.h"
#include "alien.h"
#include "mystery_ship.h"

class Game {
    private:
        Player player;
        std::vector<Obstacle> obstacles;
        std::vector<Alien> aliens;
        std::vector<Laser> alienLasers;
        i32 aliensDirection = 1;
        f64 timeLastAlienFired = 0;
        constexpr static f32 alienShootInterval = 350 / 1000.f;
        MysteryShip mysteryShip;
        f32 mysteryShipSpawnInterval = 10;
        f64 timeLastMysteryShipSpawn = 0;
        Font monogramFont{};
        int score = 0;
        int highestScore = 0;
        Music music{};
        Sound explosionSound{};

        void deleteInactiveLasers();
        std::vector<Obstacle> createObstacles();
        std::vector<Alien> createAliens();
        void moveDownAliens(f32 distance);
        void alienShootLaser(f32 laserSpeed);
        void checkCollisions();
        void gameOver();
        void resetGame();
        void initGame();
        void drawUI() const;
        void addScore(i32 s);
        void saveHighScoreToFile() const;
        int loadHighScoreFromFile() const;
        void loadSounds();

    public:
        static bool debug;
        int playerLives = 3;
        bool isRunning = false;

        Game();
        ~Game();

        void Update(f32 deltaTime);
        void HandleInput();
        void Draw();
        void Close();
};
