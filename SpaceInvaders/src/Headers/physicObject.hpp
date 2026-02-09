#pragma once
#include "renderable.hpp"
#include "Utils.hpp"
#include "raylib.h"
#include "Event.hpp"
#include "TriggerComponent.hpp"

class PhysicObject: public Renderable
{
public:

    PhysicObject();

    Event<PhysicObject*> OnTriggerEnter;

    virtual void Update();
    virtual Rectangle GetCollider() { return collider; }
    
    Rectangle collider = {position.x, position.y, (float)image.width, (float)image.height};
    bool wasTriggered = false;
};