#include "Headers/alien.hpp"
#include "iostream"

Texture2D Alien::alienImages[3] = {};
int Alien::aliensMoveDirection = 1;

Alien::Alien(Vector2 position, int type)
{
    this -> position = position;
    this -> type = type;

    if (alienImages[type - 1].id == 0)
    {
        switch (type)
        {
            default:
            case 1:
                alienImages[0] = LoadTexture("Graphics/alien_1.png");
                break;
            case 2:
                alienImages[1] = LoadTexture("Graphics/alien_2.png");
                break;
            case 3:
                alienImages[2] = LoadTexture("Graphics/alien_3.png");
                break;
        }
    }
    image = alienImages[type - 1];
}

void Alien::Update()
{
    position.x += aliensMoveDirection;
}

void Alien::Draw()
{
    DrawTextureV(alienImages[type - 1], position, WHITE);
}

void Alien::OnHit(PhysicObject* p)
{
    if (auto* laser = static_cast<Laser*>(p))
    {
        if (!laser->IsPlayerLaser())
            return;

        std::cout << "Alien hit" << std::endl;
    }
}

Rectangle Alien::GetCollider()
{
    return Rectangle{position.x, position.y, 
        static_cast<float>(alienImages[type - 1].width), 
        static_cast<float>(alienImages[type - 1].height)};
}

void Alien::UnloadAlienTextures()
{
    for (int i = 0; i < 3; i++)
    {
        UnloadTexture(alienImages[i]);
    }
}

void Alien::ChangeDirection()
{
    aliensMoveDirection *= -1;
}

void Alien::AlienShoot()
{
    std::cout << "Alien shooting!" << std::endl;
    Laser laser = Laser({
        position.x + alienImages[
            type - 1].width / 2, 
        position.y + alienImages[
            type - 1].height}, 6, true);

    Laser* pLaser = &laser;

    OnLaserShot.Invoke(pLaser);
}
