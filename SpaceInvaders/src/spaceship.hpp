#pragma once
#include "raylib.h"
#include "renderable.hpp"

class Spaceship: public Renderable
{
    public:
        Spaceship();
        ~Spaceship();

        void MoveLeft();
        void MoveRight();
        void Fire();

        void Draw() override;

    private:
        //Texture image;
        //Vector2 position;
        int speed = 7;
};