#ifndef HUDMANAGER_HPP
#define HUDMANAGER_HPP

#pragma once

#include <iostream>
#include "raylib.h"

class Game;

class HudManager
{
public:

    HudManager();
    ~HudManager();

    void Update(Game* game);

    void SetLifes(int lifes);
    void SetScore(int score);
    void SetHighScore(int highscore);
    std::string FormatWithLeadingZeros(int number, int totalDigits);

private:
    Font font;
    Texture2D spaceshipImage;
};

#endif