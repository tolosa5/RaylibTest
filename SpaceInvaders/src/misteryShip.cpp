#include "misteryShip.hpp"

MisteryShip::MisteryShip()
{
    image = LoadTexture("Graphics/mystery.png");
    alive = false;
    speed = 3;
}

MisteryShip::~MisteryShip()
{
    UnloadTexture(image);
}

void MisteryShip::Update()
{
    if (!alive)
        return;
    
    position.x += speed;

    if (Utils::IsOutOfScreenSidewards(position, image.width))
        alive = false;
}

void MisteryShip::Draw()
{
    Renderable::Draw();
}

Rectangle MisteryShip::GetCollisionBox()
{
    if (alive)
        Renderable::GetCollisionBox();
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
            position.x = 0;
            speed = 3;
        }
        else
        {
            position.x = GetScreenWidth() - image.width;
            speed = -3;
        }
        alive = true;
    }
}
