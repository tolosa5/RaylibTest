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
        int GetSpeed() { return speed; }

        void Draw() override;

        std::vector<Laser> lasers;

    private:
        int speed;
        double lastFireTime;
        float fireCooldown = 0.5;
};