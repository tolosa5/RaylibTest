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
    InitAudioDevice();

    Game game;
    HudManager hudManager;
    AudioManager audioManager;

    while (!WindowShouldClose())
    {
        //Events
        game.HandleInput();
        
        //Update positions
        game.Update();
        audioManager.Update();

        //Draw
        BeginDrawing();
        ClearBackground(Utils::GreyBgColor());
        
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
}