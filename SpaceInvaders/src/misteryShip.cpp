#include "Headers/misteryShip.hpp"

MisteryShip::MisteryShip()
{
    image = LoadTexture("Graphics/mystery.png");
    alive = false;
    speed = 160;
}

MisteryShip::~MisteryShip()
{
    UnloadTexture(image);
}

void MisteryShip::Update(float dt)
{
    if (!alive)
        return;
    
    position.x += speed * dt;

    if (Utils::IsOutOfScreenSidewards(position, image.width))
        alive = false;
}

void MisteryShip::Draw()
{
    if (alive)
        Renderable::Draw();
}

void MisteryShip::OnLaserHit()
{
    alive = false;
}

Rectangle MisteryShip::GetCollider()
{
    if (alive)
        return collider;
    else
        return {position.x, position.y, 0, 0};
    
}

void MisteryShip::Spawn()
{
    if (!alive)
    {
        position.y = 90;
        int side = GetRandomValue(0, 1);

        if (side == 0)
        {
            position.x = Utils::GetOffset() / 2;
            speed = 160;
        }
        else
        {
            position.x = GetScreenWidth() - image.width - (Utils::GetOffset() / 2);
            speed = -160;
        }
        alive = true;
    }
}
