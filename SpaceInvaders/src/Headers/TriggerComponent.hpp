#pragma once

#include "raylib.h"
#include "iostream"
#include "Trigger.hpp"
#include "ITriggerListener.hpp"
#include "unordered_set"

using namespace std;

struct TriggerComponent
{
    Trigger trigger;
    ITriggerListener* listener = nullptr;

    unordered_set<ITriggerListener*> overlapping;

    TriggerComponent() : listener(nullptr) {}

    void Initialize(Rectangle rect, ITriggerListener* l)
    {
        trigger.bounds = rect;
        listener = l;
    }
};