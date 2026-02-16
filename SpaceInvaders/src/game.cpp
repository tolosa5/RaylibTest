#include "Headers/game.hpp"
#include "Headers/hudManager.hpp"
#include "Headers/soundManager.hpp"

#include "iostream"
#include <fstream>

Game::Game()
{
    hudmanager = new HudManager();
    audioManager = new AudioManager();
    InitGame();
}

Game::~Game()
{
    Alien::UnloadAlienTextures();
    delete hudmanager;
    audioManager->CloseAudio();
    delete audioManager;
}

void Game::InitGame()
{
    currentGameState = Playing;
    audioManager->InitAudio();

    score = 0;
    highscore = LoadHighScore();
    hudmanager->SetScore(score);
    hudmanager->SetHighScore(highscore);
    
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    
    timeLastSpawn = 0.0f;
    misteryShipSpawnCooldown = GetRandomValue(10, 20);
    
    for (auto& alien: aliens)
    {
        alien.OnLaserShot.Subscribe(
            [&](Laser laser) {
                 AliensSaveLasers(laser); });
    }

    player.OnLaserShot.Subscribe(
        [&]() {
            audioManager->PlayLaserSound(); });

    player.OnPlayerDeath.Subscribe(
        [&]() {
            GameOver(); });
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

void Game::Update(float dt)
{
    audioManager->Update();
    hudmanager->Update(this);

    switch (currentGameState)
    {
        case MainMenu:
            break;
        case Playing:
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
                laser.Update(dt);
            }

            for (auto& alien: aliens)
            {
                alien.Update(dt);
            }

            for (auto& laser: alienLasers)
            {
                laser.Update(dt);
            }

            misteryShip.Update(dt);

            AliensDirectionChange();
            AliensFireOrder();
            DeleteInactiveLasers();
            CheckForCollisions();
            
            break;
        }

        case Lost:
        {
            if (IsKeyDown(KEY_ENTER))
                Reset();

            break;
        }    
        default:
            break;
    }
}

void Game::Reset()
{
    player.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();

    InitGame();
}

void Game::HandleInput(float dt)
{
    if (currentGameState != Playing)
        return;

    if (IsKeyDown(KEY_LEFT))
        player.MoveLeft(dt);

    else if (IsKeyDown(KEY_RIGHT))
        player.MoveRight(dt);

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

    float offsetY = GetScreenHeight() - (100 + Utils::GetOffset() * 2);
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

    if (currentTime - lastAlienFireTime < 
        alienLaserCooldown || aliens.empty())
        return;

    int randomAlienIndex = GetRandomValue(0, aliens.size() - 1);
    Alien& firingAlien = aliens[randomAlienIndex];
    firingAlien.AlienShoot();
    audioManager->PlayLaserSound();

    lastAlienFireTime = GetTime();
}

void Game::AliensSaveLasers(Laser laser)
{
    alienLasers.push_back(laser);
}

void Game::CheckForCollisions()
{
    for (Laser& laser : player.lasers)
    {
        auto it = aliens.begin();
        while (it != aliens.end())
        {
            if (CheckCollisionRecs(it->GetCollider(), 
            laser.GetCollider()))
            {
                int alienValue = it->value;
                it = aliens.erase(it);
                laser.LaserHit();
                ScoreChecker(alienValue);
                audioManager->PlayExplosionSound();
            }
            else
                it++;
        }

        for(Obstacle& obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it->GetCollider(), 
                laser.GetCollider()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.LaserHit();
                }
                else
                    it++;
            }  
        }

        if (CheckCollisionRecs(misteryShip.GetCollider(), 
            laser.GetCollider()))
        {
            misteryShip.OnLaserHit();
            laser.LaserHit();
            ScoreChecker(misteryShip.value);
            audioManager->PlayExplosionSound();
        }
    }


    for (Laser& laser : alienLasers)
    {
        if (CheckCollisionRecs(laser.GetCollider(), player.GetCollider()))
        {
            player.OnHit();
            laser.LaserHit();
            audioManager->PlayExplosionSound();
        }

        for(Obstacle& obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it->GetCollider(), 
                    laser.GetCollider()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.LaserHit();
                }
                else
                    it++;
            }  
        }
    }

    for(auto& alien : aliens)
    {
        for(Obstacle& obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it->GetCollider(), alien.GetCollider()))
                    it = obstacle.blocks.erase(it);
                else
                    it++;
            }  
        }

        if (CheckCollisionRecs(player.GetCollider(), alien.GetCollider()))
            player.OnHit();
    }
}

void Game::ScoreChecker(int value)
{
    score += value;
    if (score > highscore)
    {
        highscore = score;
        SaveHighScore(highscore);
    }
}

void Game::GameOver()
{
    currentGameState = Lost;
    std::cout << "Game Over!" << std::endl;
}

void Game::SaveHighScore(int highscore)
{
    std::ofstream file("highscore.txt");
    if (file.is_open())
    {
        file << highscore;
        file.close();
    }
}

int Game::LoadHighScore()
{
    int loadedHighScore = 0;
    std::ifstream file("highscore.txt");
    if (file.is_open())
    {
        file >> loadedHighScore;
        file.close();
    }
    return loadedHighScore;
}
