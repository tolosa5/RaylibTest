#pragma once
#include "renderable.hpp"
#include "Utils.hpp"
#include "raylib.h"

class Hitteable: public Renderable
{
public:
    virtual void OnHit()
    {
        
    }
};