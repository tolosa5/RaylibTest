#pragma once
#include "raylib.h"
#include "Utils.hpp"

class Renderable
{
    public:
        Renderable();
        
        virtual void Draw();
        Vector2 GetPosition() { return position; }
        virtual Rectangle GetCollisionBox() 
        {
            return {position.x, position.y, image.width, image.height}; 
        }
        
    protected:
        Texture2D image;
        Vector2 position;
};