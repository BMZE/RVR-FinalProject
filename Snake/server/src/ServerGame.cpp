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

//Initializes game (tilemap, players, fruit)
void ServerGame::Init()
{
    InitTilemap();//Create TileMap
    
    _gameObjects.reserve(3);

    InitPlayers();
    
    //Init fruit 
    _fruit = new ServerFruit(20, 5);
    _gameObjects.push_back(_fruit);
    _tilemap[20][5] = _fruit;
}

//Updates active GameObjects
void ServerGame::Update()
{
    for(auto* go : _gameObjects)
        go->Update();
}


#pragma region PLAYER MANAGEMENT

//Creates depending if Player 1 || Player 2
void ServerGame::InitPlayers()
{
    _players.reserve(2);

    int x = 25; int y = 19;
    
    ServerPlayer* player = new ServerPlayer(x, y, this, 0);
    _gameObjects.push_back(player);
    _players.push_back(player);

    _tilemap[x][y] = _gameObjects[0]; //player 1 head node

    x = 5; y = 19;
    player = new ServerPlayer(x, y, this, 1);
    _gameObjects.push_back(player);
    _players.push_back(player);

    _tilemap[x][y] = _gameObjects[1]; //player 2 head node
}

//Call to make when a snake has collided
void ServerGame::PlayerCollided()
{
    _gameLost = true;
}

//Sets other player's new input info
void ServerGame::SetInputInfo(InputInfo* info)
{
    for(int i = 0; i < _players.size(); i++)
        _players[i]->SetInputInfo(&info[i]);
} 

#pragma endregion

//Relocates fruit once eaten, chooses new fruit location
void ServerGame::FruitEaten(int x, int y)
{
    _tilemap[x][y] = nullptr; //reset tile

    FruitInfo info = _fruit->Rellocate(this); //new fruit position

    SendToClients(Message (Message::FRUIT_EATEN, info));
}

// Sends message to all clients
void ServerGame::SendToClients(Message msg)
{
    _server->SendToClients(msg);
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
        _tilemap[i].resize(height, nullptr);
    } 
}

//Returns the tile map info
std::vector<std::vector<GameObject*>> ServerGame::GetTilemap()
{
    return _tilemap;
}

//Modifies info in tile map
void ServerGame::SetTile(int x, int y, GameObject* go)
{
    _tilemap[x][y] = go;
}

#pragma endregion

ServerGame::~ServerGame()
{
    //delete GameObjects allocated memory
    for (auto go : _gameObjects)
        delete go;

    _gameObjects.clear();
    _tilemap.clear();
    _players.clear();
    _fruit = nullptr;
}