#include "game.hpp"
#include "iostream"

Game::Game()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();

    for (auto& alien: aliens)
    {
        alien.OnRayShot.Subscribe([this](Laser laser) {
            alienLasers.push_back(laser);
        });
    }
    
    misteryShipSpawnCooldown = GetRandomValue(10, 20);
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
        if (!it -> isActive())
            it = player.lasers.erase(it);
        else
            ++it;
    }

    for (auto it = alienLasers.begin(); it != alienLasers.end(); )
    {
        if (!it -> isActive())
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

    std::cout << "Created " << aliens.size() << " aliens." << std::endl;
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
