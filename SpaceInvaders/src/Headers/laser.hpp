#pragma once
#include "raylib.h"
#include "Utils.hpp"
#include "IHitteable.hpp"

class Laser: public PhysicObject, public ITriggerListener
{
    public:
        Laser(Vector2 startPosition, int speed, bool isPlayerLaser);

        void Update();
        void Draw() override;

        Rectangle GetCollider() override;
        bool IsPlayerLaser() { return isPlayerLaser; }

        bool IsActive() { return active; }

        TriggerComponent triggerComponent;

    private:
        int speed = -5;
        float laserWidth = 4;
        float laserHeight = 15;
        bool active;
        bool isPlayerLaser;
};