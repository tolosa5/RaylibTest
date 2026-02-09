#include "raylib.h"
#include "iostream"

struct Trigger
{
    Rectangle bounds;
    bool isTrigger = true;

    void SetPosition(Vector2 pos)
    {
        bounds.x = pos.x;
        bounds.y = pos.y;
    }
};