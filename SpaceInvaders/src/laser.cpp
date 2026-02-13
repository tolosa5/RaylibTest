#include "Headers/laser.hpp"
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
        if (Utils::IsOutOfScreenUpwards(position, laserHeight))
            active = false;
    }
}

void Laser::LaserHit()
{
    active = false;
}

Rectangle Laser::GetCollider() 
{
    return {position.x, position.y, (float)laserWidth, (float)laserHeight};
}