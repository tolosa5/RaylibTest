#pragma once
#include "spaceship.hpp"
#include "laser.hpp"

class Game
{
    public:
        Game();
        ~Game();

        void Update();
        void Draw();
        void HandleInput();

    private:
        Spaceship player;
        Laser laser = Laser({100, 100}, 7);
};