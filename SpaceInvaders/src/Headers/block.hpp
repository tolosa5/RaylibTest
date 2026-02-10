#pragma once
#include "raylib.h"
#include "physicObject.hpp"
#include "laser.hpp"

class Block: public PhysicObject, ITriggerListener
{
    public:
        Block(Vector2 position);
        void Draw() override;
        Rectangle GetCollider() override;

        void OnLaserHit();
        void OnTriggerEnter(ITriggerListener* other) override;

        int size = 3;
        TriggerComponent triggerComponent;
};