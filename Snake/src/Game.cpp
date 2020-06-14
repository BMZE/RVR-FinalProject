#include "Game.h"
#include "Player.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Fruit.h"
#include <iostream>
#include <Platform.h>

Game::Game()
{
    InitTilemap();//Create TileMap

    //TODO: final 
    //create players
    int x = 400; int y = 500;
    x /= TILE_PIXEL_SIZE;
    y /= TILE_PIXEL_SIZE;

    _gameObjects.reserve(2);
    _gameObjects.push_back(new Player(x, y, TILE_PIXEL_SIZE, "bin/Assets/Red.bmp", this));
    
    _tilemap[x][y].empty = false; //player head node
    _tilemap[x][y].go = _gameObjects[0];

    _gameObjects.push_back(new Fruit(20, 5, TILE_PIXEL_SIZE, "bin/Assets/apple.bmp"));
    _tilemap[20][5].empty = false;
    _tilemap[20][5].go = _gameObjects[1];
}

//Updates active GameObjects
void Game::Update()
{
    if(!Platform::IsPaused())
    {
        for(size_t i = 0; i < _gameObjects.size(); i++)
        _gameObjects[i]->Update();
    }
}

//Renders active GameObjects
void Game::Render()
{   
    for(size_t i = 0; i < _gameObjects.size(); i++)
        _gameObjects[i]->Render();
}



//Relocates fruit once eaten
void Game::FruitEaten(int x, int y)
{
    GameObject* fruit = _tilemap[x][y].go; //save fruit GameObject
    _tilemap[x][y] = Tile(); //reset tile

    for(size_t i = 0; i < _gameObjects.size(); i++)
    {
        if(_gameObjects[i] == fruit)
        {
            static_cast<Fruit*>(_gameObjects[i])->Rellocate(this);
        }
    }
}

#pragma region TILE MAP

//Initializes the tile map
void Game::InitTilemap()
{
    //number of tiles depending on window size
    int width = Renderer::GetScreenWidth() / TILE_PIXEL_SIZE;
    int height = Renderer::GetScreenHeight() / TILE_PIXEL_SIZE;

    //initial tilemap info
    _tilemap.resize(width);
    for(int i = 0; i < width; i++)
    {
        Tile tile;
        _tilemap[i].resize(height, tile);
    } 
}

//Returns the tile map info
std::vector<std::vector<Tile>> Game::GetTilemap()
{
    return _tilemap;
}

//Modifies info in tile map
void Game::SetTile(int x, int y, Tile tile)
{
    _tilemap[x][y] = tile;
}

#pragma endregion

Game::~Game()
{
   //TODO: release players
   //TODO: releasetiles
}