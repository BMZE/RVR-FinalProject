#include "Game.h"
#include "Player.h"


Game::Game()
{
    _players.reserve(1);
    _players.push_back(new Player(50, 50, 20, 20, "bin/Assets/Red.bmp"));
}

void Game::Update()
{

}

void Game::Render()
{   
    for(size_t i = 0; i < _players.size(); i++)
        _players[i]->Render();
}

void Game::HandleInput()
{
    
}

Game::~Game()
{
   //release players
}