#include <raylib.h>
#include "Headers/game.hpp"
#include "Headers/hudManager.hpp"

int main() 
{
    const int screenWidth = 750;
    const int screenHeight = 700;

    InitWindow(screenWidth + Utils::GetOffset(), 
        screenHeight + (2 * Utils::GetOffset()), 
        "Space Invaders Copy");
    
    SetTargetFPS(60);

    Game game;
    HudManager hudManager;

    while (!WindowShouldClose())
    {
        //Events
        if (game.currentGameState == Playing)
            game.HandleInput();
        
        //Update positions
        game.Update();
        hudManager.Update(&game);

        //Draw
        BeginDrawing();
        ClearBackground(Utils::GreyBgColor());
        
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}