#pragma once
#include "raylib.h"
#include "renderable.hpp"
#include "Utils.hpp"

class Laser
{
    public:
        Laser(Vector2 startPosition, int speed);

        void Update();
        void Draw();

        bool isActive() { return active; }

    private:
        Vector2 position;
        int speed = -5;
        int laserWidth = 4;
        int laserHeight = 15;
        bool active;
};