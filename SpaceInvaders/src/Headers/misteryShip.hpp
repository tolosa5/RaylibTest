#pragma once
#include "raylib.h"
#include "physicObject.hpp"
#include "ITriggerListener.hpp"
#include "IHitteable.hpp"
#include "laser.hpp"

class MisteryShip: public PhysicObject, public ITriggerListener
{
    public:
        MisteryShip();
        ~MisteryShip();

        void Update();
        void Draw() override;
        Rectangle GetCollider() override;
        void Spawn();
        void OnLaserHit();
        void OnTriggerEnter(ITriggerListener* other) override;

        bool alive;
        TriggerComponent triggerComponent;

    private:
        int speed;
};