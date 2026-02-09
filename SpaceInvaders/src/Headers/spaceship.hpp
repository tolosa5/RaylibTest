#pragma once
#include "raylib.h"
#include "laser.hpp"
#include "vector"

class Spaceship: public PhysicObject, IHitteable, ITriggerListener
{
    public:
        Spaceship();
        ~Spaceship();

        void MoveLeft();
        void MoveRight();
        void Fire();
        int GetSpeed() { return speed; }
        void OnHit(PhysicObject* p) override;

        void Draw() override;

        std::vector<Laser> lasers;

    private:
        int speed;
        double lastFireTime;
        float fireCooldown = 0.5;
};