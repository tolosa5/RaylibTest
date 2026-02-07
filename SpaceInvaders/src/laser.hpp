#pragma once
#include "raylib.h"
#include "renderable.hpp"
#include "Utils.hpp"

class Laser: public Renderable
{
    public:
        Laser(Vector2 startPosition, int speed);

        void Update();
        void Draw() override;
        Rectangle GetCollisionBox() override;

        bool isActive() { return active; }

    private:
        int speed = -5;
        int laserWidth = 4;
        int laserHeight = 15;
        bool active;
};