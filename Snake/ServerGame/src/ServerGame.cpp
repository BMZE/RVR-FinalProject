#include "ServerGame.h"
#include "ServerPlayer.h"
#include "GameObject.h"
#include "ServerFruit.h"
#include "FruitInfo.h"
#include "InputInfo.h"
#include "Server.h"
#include "Message.h"

#include <iostream>

ServerGame::ServerGame(Server* server) : _server(server)
{

}

void ServerGame::Init()
{
    InitTilemap();//Create TileMap
    
    //_gameObjects.reserve(3);
    _gameObjects.reserve(1);

    //InitPlayers();
    
    //Init fruit 
    _fruit = new ServerFruit(20, 5);
    _gameObjects.push_back(_fruit);
    _tilemap[20][5].empty = false;
    _tilemap[20][5].go = _fruit;

    //TODO: SEND FRUIT & PLAYER POSITIONS
}

//Updates active GameObjects
void ServerGame::Update()
{
    if(test == 2000)
    {
        FruitEaten(20,5);
    }
    test++;
    for(auto* go : _gameObjects) //update gameobjects
        go->Update();
}

//Creates depending if Player 1 || Player 2
void ServerGame::InitPlayers()
{
    int x = 25; int y = 19;
    
    _gameObjects.push_back(new ServerPlayer(x, y, this));
    
    _tilemap[x][y].empty = false; //player head node
    _tilemap[x][y].go = _gameObjects[0];

    x = 5; y = 19;
    _gameObjects.push_back(new ServerPlayer(x, y, this));
    
    _tilemap[x][y].empty = false; //player head node
    _tilemap[x][y].go = _gameObjects[1];
}

//Sets other player's new input info
void ServerGame::SetInputInfo(InputInfo* info)
{
    //_otherPlayer->SetInputInfo(info);
} 

//Relocates fruit once eaten, chooses new fruit location
void ServerGame::FruitEaten(int x, int y)
{
    _tilemap[x][y] = Tile(); //reset tile

    FruitInfo info = _fruit->Rellocate(this);

    _server->SendToClients(Message (Message::FRUIT_EATEN, info));
}

#pragma region TILE MAP

//Initializes the tile map
void ServerGame::InitTilemap()
{
    //number of tiles adapted from window size / TILE_PIXEL_SIZE
    int width = 30;
    int height = 20;

    //initial tilemap info
    _tilemap.resize(width);
    for(int i = 0; i < width; i++)
    {
        Tile tile;
        _tilemap[i].resize(height, tile);
    } 
}

//Returns the tile map info
std::vector<std::vector<Tile>> ServerGame::GetTilemap()
{
    return _tilemap;
}

//Modifies info in tile map
void ServerGame::SetTile(int x, int y, Tile tile)
{
    _tilemap[x][y] = tile;
}

#pragma endregion

ServerGame::~ServerGame()
{
   //TODO: release players
   //TODO: release tiles
   //TODO: releas fruit
}