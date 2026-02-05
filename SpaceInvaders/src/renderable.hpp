#pragma once
#include "raylib.h"

class Renderable
{
    public:
        Renderable();
        
        virtual void Draw();
        
    protected:
        Texture2D image;
        Vector2 position;
};