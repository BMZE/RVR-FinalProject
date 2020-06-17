#include "Game.h"
#include "Player.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Fruit.h"
#include <iostream>
#include <Platform.h>
#include "Client.h"
#include "FruitInfo.h"
//#include "InputInfo.h"

Game::Game()
{

}

void Game::Init()
{
    InitTilemap();//Create TileMap

    //TODO: final 
    //create players
    _gameObjects.reserve(3);
    
    InitPlayers();
    
    //Init fruit 
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
        for(auto* go : _gameObjects) //update gameobjects
            go->Update();
    }
}


//Renders active GameObjects
void Game::Render()
{   
    for(auto* go : _gameObjects)
        go->Render();
}

//Creates depending if Player 1 || Player 2
void Game::InitPlayers()
{
    if(Client::GetID() == '1') //player 1
    {
        int x = 25; int y = 19;
    
        _gameObjects.push_back(new Player(x, y, TILE_PIXEL_SIZE, "bin/Assets/Red.bmp", true, this));
    
        _tilemap[x][y].empty = false; //player head node
        _tilemap[x][y].go = _gameObjects[0];

        x = 5; y = 19;
        _otherPlayer = new Player(x, y, TILE_PIXEL_SIZE, "bin/Assets/Blue.bmp", false, this);
        _gameObjects.push_back(_otherPlayer);
    
        _tilemap[x][y].empty = false; //player head node
        _tilemap[x][y].go = _otherPlayer;
    }
    else if(Client::GetID() == '2') //player 2
    {
        int x = 5; int y = 19;
    
        _gameObjects.push_back(new Player(x, y, TILE_PIXEL_SIZE, "bin/Assets/Red.bmp", true, this));
    
        _tilemap[x][y].empty = false; //player head node
        _tilemap[x][y].go = _gameObjects[0];

        x = 25; y = 19;

        _otherPlayer = new Player(x, y, TILE_PIXEL_SIZE, "bin/Assets/Blue.bmp", false, this);
        _gameObjects.push_back(_otherPlayer);
    
        _tilemap[x][y].empty = false; //player head node
        _tilemap[x][y].go = _otherPlayer;
    }
    else
    {
        std::cout << "Error creating players\n";
    }
    
    
}

//Sets other player's new input info
void Game::SetInputInfo(InputInfo* info)
{
    _otherPlayer->SetInputInfo(info);
} 

#pragma region FRUIT RELOCATION

//Relocates fruit once eaten, does NOT select new fruit location
void Game::FruitRellocated(FruitInfo* info)
{
    _tilemap[_fruit->GetPosition().x][_fruit->GetPosition().y] = Tile(); //reset old tile
    _fruit->SetNewPosition(info->x, info->y, this);
    _otherPlayer->AddNode(); //add node to the other player
}

//Relocates fruit once eaten, chooses new fruit location
void Game::FruitEaten(int x, int y)
{
    _tilemap[x][y] = Tile(); //reset tile

    FruitInfo info = _fruit->Rellocate(this);
    Client::SendFruit(info);
}

#pragma endregion

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