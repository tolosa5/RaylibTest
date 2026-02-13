#ifndef GAME_HPP
#define GAME_HPP

#pragma once
#include "Event.hpp"
#include "spaceship.hpp"
#include "laser.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "misteryShip.hpp"

class HudManager;

enum GameState
{
    MainMenu,
    Playing,
    Lost
};

class Game
{
    public:
        Game();
        ~Game();

        void Update();
        void Draw();
        void HandleInput();

        GameState currentGameState = Playing;
        Spaceship player;
        int score;

    private:
        void InitGame();
        void Reset();

        void DeleteInactiveLasers();

        std::vector<Obstacle> CreateObstacles();

        std::vector<Alien> CreateAliens();
        void AliensDirectionChange();
        void AliensMoveDown();
        void AliensFireOrder();
        void AliensSaveLasers(Laser laser);
        void CheckForCollisions();
        void ScoreChecker(int value);
        void GameOver();


        std::vector<Obstacle> obstacles;
        int obstacleNumber = 4;

        std::vector<Alien> aliens;
        int alienRows = 5;
        int alienCols = 11;
        int aliensDirection;
        std::vector<Laser> alienLasers;
        constexpr static float alienLaserCooldown = 0.4f;
        float lastAlienFireTime = 0.0f;

        MisteryShip misteryShip;
        float misteryShipSpawnCooldown;
        float timeLastSpawn;

        HudManager* hudmanager;
};

#endif