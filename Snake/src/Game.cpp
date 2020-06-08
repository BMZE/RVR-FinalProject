#include "Game.h"
#include "Player.h"
#include "Renderer.h"

Game::Game()
{
    //create players
    int x = 400; int y = 500;
    x /= TILE_PIXEL_SIZE;
    y /= TILE_PIXEL_SIZE;

    _players.reserve(1);
    _players.push_back(new Player(x, y, 20, 20, "bin/Assets/Red.bmp"));
    
    //number of tiles
    int width = Renderer::GetScreenWidth() / TILE_PIXEL_SIZE;
    int height = Renderer::GetScreenHeight() / TILE_PIXEL_SIZE;

    //tilemap info
    _tilemap.resize(width);
    for(int i = 0; i < width; i++)
        _tilemap[i].resize(height, false);

  

    _tilemap[x][y] = true; //player head node
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