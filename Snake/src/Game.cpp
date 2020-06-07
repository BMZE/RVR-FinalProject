#include "Game.h"
#include "Player.h"

Game::Game()
{
    _players.reserve(1);
    _players.push_back(new Player(400, 500, 20, 20, "bin/Assets/Red.bmp"));
}

void Game::Update()
{
    for(size_t i = 0; i < _players.size(); i++)
        _players[i]->Update();
}

void Game::Render()
{   
    for(size_t i = 0; i < _players.size(); i++)
        _players[i]->Render();
}

Game::~Game()
{
   //release players
}