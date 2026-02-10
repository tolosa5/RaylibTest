#pragma once
#include "raylib.h"
#include "laser.hpp"
#include "vector"

class Spaceship: public PhysicObject, public ITriggerListener
{
    public:
        Spaceship();
        ~Spaceship();

        void MoveLeft();
        void MoveRight();
        void Fire();
        int GetSpeed() { return speed; }
        void OnLaserHit();
        void OnTriggerEnter(ITriggerListener* other) override;

        void Draw() override;

        std::vector<Laser> lasers;

        TriggerComponent triggerComponent;

    private:
        int speed;
        double lastFireTime;
        float fireCooldown = 0.5;
};