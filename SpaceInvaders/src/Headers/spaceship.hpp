#pragma once
#include "raylib.h"
#include "laser.hpp"
#include "vector"

class Spaceship: public PhysicObject
{
    public:
        Spaceship();
        ~Spaceship();

        void MoveLeft();
        void MoveRight();
        void Fire();
        void OnHit();
        void Death();
        int GetSpeed() { return speed; }
        void Draw() override;

        std::vector<Laser> lasers;
        Event<const int*> OnPlayerDeath;

    private:
        int speed;
        const int maxPlayerLifes = 3;
        int currentPlayerLifes;
        int score;
        double lastFireTime;
        float fireCooldown = 0.5;
        
};