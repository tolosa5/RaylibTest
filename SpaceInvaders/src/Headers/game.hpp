#pragma once
#include "Event.hpp"
#include "spaceship.hpp"
#include "laser.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "misteryShip.hpp"
#include "TriggerSystem.hpp"

class Game
{
    public:
        Game();
        ~Game();

        void Update();
        void Draw();
        void HandleInput();

    private:
        void DeleteInactiveLasers();

        std::vector<Obstacle> CreateObstacles();

        std::vector<Alien> CreateAliens();
        void AliensDirectionChange();
        void AliensMoveDown();
        void AliensFireOrder();
        void AliensSaveLasers(Laser laser);

        void InitializeTriggers();

        Spaceship player;

        std::vector<Obstacle> obstacles;
        int obstacleNumber = 4;

        std::vector<Alien> aliens;
        int alienRows = 5;
        int alienCols = 11;
        int aliensDirection;
        std::vector<Laser> alienLasers;
        constexpr static float alienLaserCooldown = 0.3f;
        float lastAlienFireTime = 0.0f;

        MisteryShip misteryShip;
        float misteryShipSpawnCooldown;
        float timeLastSpawn;

        TriggerSystem triggerSystem;
};