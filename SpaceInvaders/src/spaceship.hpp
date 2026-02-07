#pragma once
#include "raylib.h"
#include "hitteable.hpp"
#include "laser.hpp"
#include "vector"

class Spaceship: public Hitteable
{
    public:
        Spaceship();
        ~Spaceship();

        void MoveLeft();
        void MoveRight();
        void Fire();
        int GetSpeed() { return speed; }

        void Draw() override;

        std::vector<Laser> lasers;

    private:
        int speed;
        double lastFireTime;
        float fireCooldown = 0.5;
};