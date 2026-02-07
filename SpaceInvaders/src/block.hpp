#pragma once
#include "raylib.h"
#include "hitteable.hpp"

class Block: public Hitteable
{
    public:
        Block(Vector2 position);
        void Draw() override;
        Rectangle GetCollisionBox() override;
        int size = 3;
};