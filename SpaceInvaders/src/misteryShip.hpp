#pragma once
#include "raylib.h"
#include "hitteable.hpp"

class MisteryShip: public Hitteable
{
    public:
        MisteryShip();
        ~MisteryShip();

        void Update();
        void Draw() override;
        Rectangle GetCollisionBox() override;
        void Spawn();


        bool alive;

    private:
        int speed;
};