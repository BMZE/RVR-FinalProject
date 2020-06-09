#include "Game.h"
#include "Player.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Fruit.h"
#include <iostream>

Game::Game()
{
    //Create TileMap

    //number of tiles
    int width = Renderer::GetScreenWidth() / TILE_PIXEL_SIZE;
    int height = Renderer::GetScreenHeight() / TILE_PIXEL_SIZE;

    //initial tilemap info
    _tilemap.resize(width);
    for(int i = 0; i < width; i++)
    {
        Tile tile;
        _tilemap[i].resize(height, tile);
    } 

    //create players
    int x = 400; int y = 500;
    x /= TILE_PIXEL_SIZE;
    y /= TILE_PIXEL_SIZE;

    _gameObjects.reserve(2);
    _gameObjects.push_back(new Player(x, y, 20, 20, "bin/Assets/Red.bmp", this));
    
    _tilemap[x][y].empty = false; //player head node
    _tilemap[x][y].go = _gameObjects[0];

    _gameObjects.push_back(new Fruit(20, 20, 20, "bin/Assets/apple.bmp"));
    _tilemap[20][20].empty = false;
    _tilemap[20][20].go = _gameObjects[1];
}

void Game::Update()
{
    for(size_t i = 0; i < _gameObjects.size(); i++)
        _gameObjects[i]->Update();
}

void Game::Render()
{   
    for(size_t i = 0; i < _gameObjects.size(); i++)
        _gameObjects[i]->Render();
}

std::vector<std::vector<Tile>> Game::GetTilemap()
{
    return _tilemap;
}

void Game::SetTile(int x, int y, Tile tile)
{
    _tilemap[x][y] = tile;
}

Game::~Game()
{
   //TODO: release players
   //TODO: releasetiles
}