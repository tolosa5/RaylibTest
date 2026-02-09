#include "Headers/laser.hpp"
#include "iostream"

Laser::Laser(Vector2 startPosition, int speed, bool isPlayerLaser)
{
    position.x = startPosition.x;
    position.y = startPosition.y;
    this->speed = speed;
    active = true;
    this->isPlayerLaser = isPlayerLaser;
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

void Laser::OnTriggerEnter(ITriggerListener* other)
{
    if (auto* p = dynamic_cast<IHitteable*>(other))
    {
        std::cout << "Laser has hit a hitteable" << std::endl;
    }
    
}

Rectangle Laser::GetCollider()
{
    return {position.x, position.y, (float)laserWidth, (float)laserHeight};
}