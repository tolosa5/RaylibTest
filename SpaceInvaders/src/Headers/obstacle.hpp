#pragma once
#include "raylib.h"
#include "block.hpp"
#include "vector"

class Obstacle: public Renderable
{
    public:
        Obstacle(Vector2 position);
        void Draw() override;
        std::vector<Block> blocks;
        static std::vector<std::vector<int>> grid; 
};