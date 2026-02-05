#include "spaceship.hpp"

Spaceship::Spaceship()
{

    image = LoadTexture("Graphics/spaceship.png");
    position.x = (GetScreenWidth() / 2 - image.width) / 2;
    position.y = GetScreenHeight() - image.height;
}

Spaceship::~Spaceship()
{
    UnloadTexture(image);
}

void Spaceship::Draw()
{
    Renderable::Draw();
}

void Spaceship::MoveLeft()
{
    position.x -= speed;
    if (position.x < 0)
        position.x = 0;
    
}

void Spaceship::MoveRight()
{
    position.x += speed;
    if (position.x > GetScreenWidth() - image.width)
        position.x = GetScreenWidth() - image.width;
}

void Spaceship::Fire()
{
    
}