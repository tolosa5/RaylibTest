#include "laser.hpp"
#include "iostream"

Laser::Laser(Vector2 startPosition, int speed)
{
    position.x = startPosition.x;
    position.y = startPosition.y;
    this->speed = speed;
    active = true;
}

void Laser::Draw()
{
    if (active)
    {
        DrawRectangle(position.x, position.y, 
            laserWidth, laserWidth, Utils::YellowColor());
    }
}

void Laser::Update()
{
    position.y += speed;
    if (active)
    {
        if (position.y > GetScreenHeight() || position.y < 0)
        {
            active = false;
        }
    }
}