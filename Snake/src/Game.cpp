#include "Game.h"
#include "Player.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Fruit.h"
// #include <iostream>
#include <Platform.h>
#include "Client.h"
#include "FruitInfo.h"
//#include "InputInfo.h"

Game::Game()
{
    InitTilemap();//Create TileMap

    //TODO: final 
    //create players
    int x = 400; int y = 500;
    x /= TILE_PIXEL_SIZE;
    y /= TILE_PIXEL_SIZE;

    _gameObjects.reserve(3);
    _gameObjects.push_back(new Player(x, y, TILE_PIXEL_SIZE, "bin/Assets/Red.bmp", true, this));
    
    _tilemap[x][y].empty = false; //player head node
    _tilemap[x][y].go = _gameObjects[0];

    x = 200; y = 500;
    x /= TILE_PIXEL_SIZE;
    y /= TILE_PIXEL_SIZE;

    _otherPlayer = new Player(x, y, TILE_PIXEL_SIZE, "bin/Assets/Red.bmp", false, this);
    _gameObjects.push_back(_otherPlayer);
    
    _tilemap[x][y].empty = false; //player head node
    _tilemap[x][y].go = _otherPlayer;

    //FRUIT
    _fruit = new Fruit(20, 5, TILE_PIXEL_SIZE, "bin/Assets/apple.bmp");
    _gameObjects.push_back(_fruit);
    _tilemap[20][5].empty = false;
    _tilemap[20][5].go = _fruit;
}

//Updates active GameObjects
void Game::Update()
{
    if(!Platform::IsPaused())
    {
        for(size_t i = 0; i < _gameObjects.size(); i++) //update gameobjects
        {
            _gameObjects[i]->Update();
        }
    }
}


//Renders active GameObjects
void Game::Render()
{   
    for(size_t i = 0; i < _gameObjects.size(); i++)
        _gameObjects[i]->Render();
}

void Game::FruitRellocated(FruitInfo* info)
{
    std::cout << "FruitRellocated\n";
    _tilemap[_fruit->GetPosition().x][_fruit->GetPosition().y] = Tile(); //reset old tile
    _fruit->SetNewPosition(info->x, info->y, this);
    std::cout << "NEW_FRUIT_POSITION\n";
}

void Game::SetInputInfo(InputInfo* info)
{
    std::cout << "INPUT_INFO\n";
    _otherPlayer->SetInputInfo(info);
} 


//Relocates fruit once eaten
void Game::FruitEaten(int x, int y)
{
    _tilemap[x][y] = Tile(); //reset tile

    FruitInfo info = _fruit->Rellocate(this);
    Client::SendFruit(info);
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
   //TODO: release tiles
   //TODO: releas fruit
}