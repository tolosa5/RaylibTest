#pragma once

#include "raylib.h"
#include "iostream"

class ITriggerListener
{
public:
    virtual void OnTriggerEnter(ITriggerListener* other) {}
};