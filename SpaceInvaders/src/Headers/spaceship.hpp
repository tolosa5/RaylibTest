#pragma once
#include "raylib.h"
#include "laser.hpp"
#include "vector"

class Spaceship: public PhysicObject
{
    public:
        Spaceship();
        ~Spaceship();

        void Draw() override;
        void MoveLeft(float dt);
        void MoveRight(float dt);
        void Fire();
        void OnHit();
        void Death();
        void Reset();
        
        int GetSpeed() { return speed; }
        Rectangle GetCollider() override;
        int GetCurrentLifes() { return currentPlayerLifes; }

        std::vector<Laser> lasers;
        Event<> OnLaserShot;
        Event<> OnPlayerDeath;

    private:
        int speed;
        const int maxPlayerLifes = 3;
        int currentPlayerLifes;
        int score;
        double lastFireTime;
        float fireCooldown = 0.5;
        
};