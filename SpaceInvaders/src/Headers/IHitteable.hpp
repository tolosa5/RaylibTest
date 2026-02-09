#ifndef IHITTEABLE_HPP
#define IHITTEABLE_HPP

#include "raylib.h"
#include "physicObject.hpp"

class IHitteable
{
public:
    virtual void OnHit(PhysicObject* p) {}
};

#endif