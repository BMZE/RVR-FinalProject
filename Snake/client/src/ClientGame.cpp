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
    
    _gameObjects.reserve(3);
    
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
    _players.reserve(2);

    if(Client::GetID() == '0') //player 1
    {
        int x = 25; int y = 19;
    
        ClientPlayer* player = new ClientPlayer(x, y, TILE_PIXEL_SIZE, "bin/Assets/Red.bmp", true, this);
        _gameObjects.push_back(player);
        _players.push_back(player);

        x = 5; y = 19;

        player = new ClientPlayer(x, y, TILE_PIXEL_SIZE, "bin/Assets/Blue.bmp", false, this);
        _gameObjects.push_back(player);
        _players.push_back(player);
    }
    else if(Client::GetID() == '1') //player 2
    {
        int x = 25; int y = 19;
    
        ClientPlayer* player = new ClientPlayer(x, y, TILE_PIXEL_SIZE, "bin/Assets/Blue.bmp", true, this);
        _gameObjects.push_back(player);
        _players.push_back(player);

        x = 5; y = 19;

        player = new ClientPlayer(x, y, TILE_PIXEL_SIZE, "bin/Assets/Red.bmp", false, this);
        _gameObjects.push_back(player);
        _players.push_back(player);

    }
    else
    {
        std::cout << "Error creating players\n";
    }
    
    
}

void ClientGame::UpdatePlayerSnakeHead(Node* node, int player)
{
    _players[player]->SetHead(node);
}

void ClientGame::AddNodeToSnake(Node* node, int player)
{
    _players[player]->AddNode(node);
}

void ClientGame::UpdatePlayerPosition(int player)
{
    _players[player]->SetNewPosition();
}

//Sets other player's new input info
void ClientGame::SetInputInfo(InputInfo* info)
{
    _players[0]->SetInputInfo(info);
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