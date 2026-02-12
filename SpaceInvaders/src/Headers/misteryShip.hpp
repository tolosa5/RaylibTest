#pragma once
#include "raylib.h"
#include "physicObject.hpp"

class MisteryShip: public PhysicObject
{
    public:
        MisteryShip();
        ~MisteryShip();

        void Update();
        void Draw() override;
        void OnLaserHit();
        Rectangle GetCollider() override;
        void Spawn();


        bool alive;

    private:
        int speed;
};