#include "laser.hpp"

Laser::Laser(Vector2 startPosition, int speed)
{
    position.x = startPosition.x;
    position.y = startPosition.y;
}

void Laser::Draw()
{
    DrawRectangle(position.x, position.y, 
        laserWidth, laserWidth, {243, 216, 63, 255});
}

void Laser::Update()
{
}