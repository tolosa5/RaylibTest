#include "Headers/game.hpp"
#include "iostream"

Game::Game()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    InitializeTriggers();
    
    misteryShipSpawnCooldown = GetRandomValue(10, 20);
    
    for (auto& alien: aliens)
    {
        alien.OnLaserShot.Subscribe(
            [this](const Laser* laser) {
                 AliensSaveLasers(*laser); });
    }
}

Game::~Game()
{
    Alien::UnloadAlienTextures();
}

void Game::Draw()
{
    player.Draw();
    misteryShip.Draw();
    
    for (auto& laser: player.lasers)
    {
        laser.Draw();
    }

    for (auto& obstacle: obstacles)
    {
        obstacle.Draw();
    }

    for (auto& alien: aliens)
    {
        alien.Draw();
    }

    for (auto& laser: alienLasers)
    {
        laser.Draw();
    }
}

void Game::Update()
{
    double currentTime = GetTime();
    if (currentTime - timeLastSpawn > misteryShipSpawnCooldown)
    {
        misteryShip.Spawn();
        timeLastSpawn = GetTime();
        misteryShipSpawnCooldown = GetRandomValue(10, 20);
    }

    for (auto& laser: player.lasers)
    {
        laser.Update();
    }

    for (auto& alien: aliens)
    {
        alien.Update();
    }

    for (auto& laser: alienLasers)
    {
        laser.Update();
    }

    misteryShip.Update();
    triggerSystem.Update();

    AliensDirectionChange();
    AliensFireOrder();
    DeleteInactiveLasers();
}

void Game::HandleInput()
{
    if (IsKeyDown(KEY_LEFT))
        player.MoveLeft();

    else if (IsKeyDown(KEY_RIGHT))
        player.MoveRight();

    if (IsKeyDown(KEY_SPACE))
        player.Fire();
}

void Game::DeleteInactiveLasers()
{
    for (auto it = player.lasers.begin(); it != player.lasers.end(); )
    {
        if (!it -> IsActive())
            it = player.lasers.erase(it);
        else
            ++it;
    }

    for (auto it = alienLasers.begin(); it != alienLasers.end(); )
    {
        if (!it -> IsActive())
            it = alienLasers.erase(it);
        else
            ++it;
    }
}

std::vector<Obstacle> Game::CreateObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size() * Utils::PixelSize();
    float gap = (GetScreenWidth() - (obstacleNumber * obstacleWidth)) /
        (obstacleNumber + 1);

    float offsetY = GetScreenHeight() - 100;
    for(int i = 0; i < obstacleNumber; i++)
    {
        float offsetX = (i + 1) * gap + (i * obstacleWidth);

        obstacles.push_back(Obstacle({offsetX, offsetY}));
    }

    return obstacles;
}

std::vector<Alien> Game::CreateAliens()
{
    std::vector<Alien> aliens;
    for(int row = 0; row < alienRows; row++)
    {
        for (int col = 0; col < alienCols; col++)
        {
            int type;

            if(row == 0)
                type = 3;
            else if (row <= 2)
                type = 2;
            else
                type = 1;

            int cellSize = 55;
            float x = ((GetScreenWidth()
             - cellSize * alienCols) / 2) + col * cellSize;
            float y = ((GetScreenHeight()
             - cellSize * alienRows) / 4) + row * cellSize;

            aliens.push_back(Alien({x, y}, type));
        }
    }
    return aliens;
}

void Game::AliensDirectionChange()
{
    for (auto& alien: aliens)
    {
        if (Utils::IsOutOfScreenSidewards(
            alien.GetPosition(), 
            alien.alienImages[alien.type - 1].width))
        {
            alien.ChangeDirection();
            AliensMoveDown();
            break;
        }
    }
}

void Game::AliensMoveDown()
{
    for (auto& alien: aliens)
    {
        alien.MoveDown(4);
    }
}

void Game::AliensFireOrder()
{
    double currentTime = GetTime();

    if (currentTime - lastAlienFireTime < alienLaserCooldown || aliens.empty())
        return;

    int randomAlienIndex = GetRandomValue(0, aliens.size() - 1);
    Alien& firingAlien = aliens[randomAlienIndex];
    firingAlien.AlienShoot();

    lastAlienFireTime = GetTime();
}

void Game::AliensSaveLasers(Laser laser)
{
    TriggerSystem::Register(&laser.triggerComponent);
    alienLasers.push_back(laser);
}

void Game::InitializeTriggers()
{
    TriggerSystem::Register(&player.triggerComponent);
    TriggerSystem::Register(&misteryShip.triggerComponent);

    for (auto& alien: aliens)
    {
        TriggerSystem::Register(&alien.triggerComponent);
    }


    for (auto& obstacle: obstacles)
    {
        for (auto& block: obstacle.blocks)
        {
            TriggerSystem::Register(&block.triggerComponent);
        }
    }
}
