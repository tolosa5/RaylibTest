#pragma once
#include "raylib.h"

class Utils
{
    public:
        static Color YellowColor () { return {243, 216, 63, 255}; }
        static int PixelSize() { return 3; }
        static bool IsOutOfScreenSidewards(
            Vector2 position, int width = 0)
        {
            return position.x > GetScreenWidth() - width || position.x < 0;
        }

        static bool IsOutOfScreenUpwards(
            Vector2 position, int height)
        {
            return position.y > GetScreenHeight() || position.y < 0;
        }
};