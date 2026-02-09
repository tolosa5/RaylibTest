#pragma once
#include "raylib.h"
#include "Utils.hpp"
#include "IHitteable.hpp"

class Laser: public PhysicObject, ITriggerListener, IHitteable
{
    public:
        Laser(Vector2 startPosition, int speed, bool isPlayerLaser);

        void Update();
        void Draw() override;
        void OnTriggerEnter(ITriggerListener* other) override;

        Rectangle GetCollider() override;
        bool IsPlayerLaser() { return isPlayerLaser; }

        bool IsActive() { return active; }

    private:
        int speed = -5;
        float laserWidth = 4;
        float laserHeight = 15;
        bool active;
        bool isPlayerLaser;
};