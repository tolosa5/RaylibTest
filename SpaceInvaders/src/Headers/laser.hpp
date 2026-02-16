#pragma once
#include "raylib.h"
#include "Utils.hpp"
#include "physicObject.hpp"

class Laser : public PhysicObject
{
    public:
        Laser(Vector2 startPosition, int speed);

        void Update(float dt) override;
        void Draw() override;

        void LaserHit();
        Rectangle GetCollider() override;

        bool IsActive() { return active; }

    private:
        int speed = -200;
        int laserWidth = 4;
        int laserHeight = 15;
        bool active = true;
};