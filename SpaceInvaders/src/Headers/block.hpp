#pragma once
#include "raylib.h"
#include "physicObject.hpp"

class Block: public PhysicObject
{
    public:
        Block(Vector2 position);
        void Draw() override;
        Rectangle GetCollider() override;
        int size = 3;
};