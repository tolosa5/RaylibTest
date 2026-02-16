#pragma once
#include "raylib.h"
#include "physicObject.hpp"

class MisteryShip: public PhysicObject
{
    public:
        MisteryShip();
        ~MisteryShip();

        void Update(float dt) override;
        void Draw() override;
        void OnLaserHit();
        Rectangle GetCollider() override;
        void Spawn();

        int value = 500;
        bool alive;

    private:
        int speed;
};