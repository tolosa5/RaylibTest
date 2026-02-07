#include <raylib.h>
#include "game.hpp"

int main() 
{
    Color greyBg = {30, 30, 30, 255};
    const int screenWidth = 750;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "Space Invaders Copy");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose())
    {
        //Events
        game.HandleInput();

        //Update positions
        game.Update();

        //Draw
        BeginDrawing();
        ClearBackground(greyBg);
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}