#include "Headers/spaceship.hpp"
#include "iostream"

Spaceship::Spaceship()
{
    image = LoadTexture("Graphics/spaceship.png");
    position.x = (GetScreenWidth() / 2 - image.width) / 2;
    position.y = GetScreenHeight() - image.height - (Utils::GetOffset() * 2);
    speed = 7;
    lastFireTime = 0.0;
    currentPlayerLifes = maxPlayerLifes;
}

Spaceship::~Spaceship()
{
    UnloadTexture(image);
}

void Spaceship::Draw()
{
    Renderable::Draw();
}

Rectangle Spaceship::GetCollider()
{
    return {position.x, position.y, (float)image.width, (float)image.height};
}

void Spaceship::MoveLeft()
{
    position.x -= speed;
    if (position.x < (Utils::GetOffset() / 2))
        position.x = (Utils::GetOffset() / 2);
}

void Spaceship::MoveRight()
{
    position.x += speed;
    if (position.x > GetScreenWidth() - image.width - (Utils::GetOffset() / 2))
        position.x = GetScreenWidth() - image.width - (Utils::GetOffset() / 2);
}

void Spaceship::Fire()
{
    if (GetTime() - lastFireTime >= fireCooldown)
    {
        lasers.push_back(Laser({
            position.x + image.width / 2 - 2, position.y - 10},
             -5));

        lastFireTime = GetTime();
    }
}

void Spaceship::OnHit()
{
    currentPlayerLifes--;
    std::cout << "Shoot received, lifes left: " << currentPlayerLifes << std::endl;

    if (currentPlayerLifes <= 0)
        Death();
}

void Spaceship::Death()
{
    std::cout << "Player death" << std::endl;
    OnPlayerDeath.Invoke();
}

void Spaceship::Reset()
{
    position.x = (GetScreenWidth() / 2 - image.width) / 2;
    position.y = GetScreenHeight() - image.height - (Utils::GetOffset() * 2);
    currentPlayerLifes = maxPlayerLifes;
    lasers.clear();
}
