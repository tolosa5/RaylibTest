#include <raylib.h>
#include "Headers/game.hpp"
#include "Headers/hudManager.hpp"
#include "Headers/soundManager.hpp"

int main() 
{
    const int screenWidth = 750;
    const int screenHeight = 700;

    InitWindow(screenWidth + Utils::GetOffset(), 
        screenHeight + (2 * Utils::GetOffset()), 
        "Space Invaders Copy");
    
    SetTargetFPS(60);
    InitAudioDevice();

    Game game;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        //Events
        game.HandleInput(dt);
        
        //Update positions
        game.Update(dt);

        //Draw
        BeginDrawing();
        ClearBackground(Utils::GreyBgColor());
        
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
}