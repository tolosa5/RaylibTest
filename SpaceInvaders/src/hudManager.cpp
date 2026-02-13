#include "Headers/hudManager.hpp"
#include "Headers/game.hpp"

HudManager::HudManager()
{
    SetLifes(3);
    SetPoints(0);
}

HudManager::~HudManager()
{

}

void HudManager::Update(Game* game)
{
    DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 
            0.1f, 20, 2, Utils::YellowColor());
    DrawLineEx({25, 730}, {775, 730}, 3, Utils::YellowColor());
    

    if (game->currentGameState == Playing)
        DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, Utils::YellowColor());
    else if (game->currentGameState == Lost)
        DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, Utils::YellowColor());
}

void HudManager::SetLifes(int lifes)
{
    float spacing = 50.0;
    for (int i = 0; i < lifes; i++)
    {
        DrawTextureV(spaceshipImage, {spacing, 745}, WHITE);
        spacing += 50.0;
    }
}

void HudManager::SetPoints(int points)
{
    DrawTextEx(font, "SCORE", {60, 20}, 34, 2, Utils::YellowColor());

    DrawTextEx(font, FormatWithLeadingZeros(points, 5).c_str(), 
        {60, 45}, 34, 2, Utils::YellowColor());

    std::cout << "Score: " << points << std::endl;
}

std::string HudManager::FormatWithLeadingZeros(int number, int totalDigits)
{
    std::string numberStr = std::to_string(number);
    int leadingZeros = totalDigits - numberStr.length();
    return numberStr = std::string(leadingZeros, '0') + numberStr;
}
