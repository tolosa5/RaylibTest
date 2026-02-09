#pragma once
#include "raylib.h"
#include "physicObject.hpp"
#include "ITriggerListener.hpp"
#include "IHitteable.hpp"

class MisteryShip: public PhysicObject, IHitteable, ITriggerListener
{
    public:
        MisteryShip();
        ~MisteryShip();

        void Update();
        void Draw() override;
        Rectangle GetCollider() override;
        void Spawn();


        bool alive;

    private:
        int speed;
};