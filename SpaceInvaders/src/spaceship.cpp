#include "spaceship.hpp"
#include "iostream"

Spaceship::Spaceship()
{
    image = LoadTexture("Graphics/spaceship.png");
    position.x = (GetScreenWidth() / 2 - image.width) / 2;
    position.y = GetScreenHeight() - image.height;
    speed = 7;
    lastFireTime = 0.0;
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
    if (GetTime() - lastFireTime >= fireCooldown)
    {
        std::cout << "Firing laser!" << std::endl;

        lasers.push_back(Laser({
            position.x + image.width / 2 - 2, position.y - 10}, -5));

        lastFireTime = GetTime();
    }
}