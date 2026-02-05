#pragma once
#include "raylib.h"
#include "renderable.hpp"

class Laser: public Renderable
{
    public:
        Laser(Vector2 startPosition, int speed);

        void Update();
        void Draw() override;

    private:
        int speed = 10;
        int laserWidth = 4;
        int laserHeight = 15;
};