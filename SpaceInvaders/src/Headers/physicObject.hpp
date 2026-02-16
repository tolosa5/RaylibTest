#pragma once
#include "renderable.hpp"
#include "Utils.hpp"
#include "raylib.h"
#include "Event.hpp"

class PhysicObject: public Renderable
{
public:

    PhysicObject();

    virtual void Update(float dt);
    virtual Rectangle GetCollider() { return collider; }
    
    Rectangle collider = {position.x, position.y, 
        (float)image.width, (float)image.height};
};