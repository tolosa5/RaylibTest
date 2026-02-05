#include "game.hpp"

Game::Game()
{
    
}

Game::~Game()
{

}

void Game::Draw()
{
    player.Draw();
    laser.Draw();
}

void Game::Update()
{
    laser.Update();
}

void Game::HandleInput()
{
    if (IsKeyDown(KEY_LEFT))
        player.MoveLeft();

    else if (IsKeyDown(KEY_RIGHT))
        player.MoveRight();

    if (IsKeyPressed(KEY_SPACE))
        player.Fire();
}