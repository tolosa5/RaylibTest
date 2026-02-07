#pragma once
#include "raylib.h"
#include "renderable.hpp"

class Block: public Renderable
{
    public:
        Block(Vector2 position);
        void Draw() override;
        int size = 3;
};