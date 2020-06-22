#include "ClientGame.h"
#include "ClientPlayer.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ClientFruit.h"
#include <iostream>
#include <Platform.h>
#include "Client.h"
#include "FruitInfo.h"
//#include "InputInfo.h"

ClientGame::ClientGame()
{

}

void ClientGame::Init()
{
    InitTilemap();//Create TileMap

    //TODO: final 
    //create players
    // _gameObjects.reserve(3);
    
    _gameObjects.reserve(2);
    
    InitPlayers();

    //Init fruit 
    _fruit = new ClientFruit(20, 5, TILE_PIXEL_SIZE, "bin/Assets/apple.bmp");
    _gameObjects.push_back(_fruit);
    _tilemap[20][5].empty = false;
    _tilemap[20][5].go = _fruit;
}

//Updates active GameObjects
void ClientGame::Update()
{
    // if(!Platform::IsPaused())
    // {
    //     for(auto* go : _gameObjects) //update gameobjects
    //         go->Update();
    // }
}


//Renders active GameObjects
void ClientGame::Render()
{   
    for(auto* go : _gameObjects)
        go->Render();
}

//Creates depending if Player 1 || Player 2
void ClientGame::InitPlayers()
{
    int x = 20; int y = 15;
    _otherPlayer = new ClientPlayer(x, y, TILE_PIXEL_SIZE, "bin/Assets/Red.bmp", true, this);
    _gameObjects.push_back(_otherPlayer);
    
    _tilemap[x][y].empty = false; //player head node
    _tilemap[x][y].go = _gameObjects[0];

    // if(Client::GetID() == '1') //player 1
    // {
    //     int x = 25; int y = 19;
    
    //     _gameObjects.push_back(new ClientPlayer(x, y, TILE_PIXEL_SIZE, "bin/Assets/Red.bmp", true, this));
    
    //     _tilemap[x][y].empty = false; //player head node
    //     _tilemap[x][y].go = _gameObjects[0];

    //     x = 5; y = 19;
    //     _otherPlayer = new ClientPlayer(x, y, TILE_PIXEL_SIZE, "bin/Assets/Blue.bmp", false, this);
    //     _gameObjects.push_back(_otherPlayer);
    
    //     _tilemap[x][y].empty = false; //player head node
    //     _tilemap[x][y].go = _otherPlayer;
    // }
    // else if(Client::GetID() == '2') //player 2
    // {
    //     int x = 5; int y = 19;
    
    //     _gameObjects.push_back(new ClientPlayer(x, y, TILE_PIXEL_SIZE, "bin/Assets/Red.bmp", true, this));
    
    //     _tilemap[x][y].empty = false; //player head node
    //     _tilemap[x][y].go = _gameObjects[0];

    //     x = 25; y = 19;

    //     _otherPlayer = new ClientPlayer(x, y, TILE_PIXEL_SIZE, "bin/Assets/Blue.bmp", false, this);
    //     _gameObjects.push_back(_otherPlayer);
    
    //     _tilemap[x][y].empty = false; //player head node
    //     _tilemap[x][y].go = _otherPlayer;
    // }
    // else
    // {
    //     std::cout << "Error creating players\n";
    // }
    
    
}

void ClientGame::UpdatePlayerSnakeHead(Node* node)
{
    _otherPlayer->SetHead(node);
}

void ClientGame::AddNodeToSnake(Node* node)
{
    _otherPlayer->AddNode(node);
}

void ClientGame::UpdatePlayerPosition()
{
    _otherPlayer->SetNewPosition();
}

//Sets other player's new input info
void ClientGame::SetInputInfo(InputInfo* info)
{
    _otherPlayer->SetInputInfo(info);
} 

#pragma region FRUIT RELOCATION

//Relocates fruit once eaten, does NOT select new fruit location
void ClientGame::FruitRellocated(FruitInfo* info)
{
    _tilemap[_fruit->GetPosition().x][_fruit->GetPosition().y] = Tile(); //reset old tile
    _fruit->SetNewPosition(info->x, info->y, this);
}

//Relocates fruit once eaten, chooses new fruit location
void ClientGame::FruitEaten(int x, int y)
{
    _tilemap[x][y] = Tile(); //reset tile

    FruitInfo info = _fruit->Rellocate(this);
    Client::SendFruit(info);
}

#pragma endregion

#pragma region TILE MAP

//Initializes the tile map
void ClientGame::InitTilemap()
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
std::vector<std::vector<Tile>> ClientGame::GetTilemap()
{
    return _tilemap;
}

//Modifies info in tile map
void ClientGame::SetTile(int x, int y, Tile tile)
{
    _tilemap[x][y] = tile;
}

#pragma endregion

ClientGame::~ClientGame()
{
   //TODO: release players
   //TODO: release tiles
   //TODO: releas fruit
}