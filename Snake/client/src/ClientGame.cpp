#include "ClientGame.h"
#include "ClientPlayer.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ClientFruit.h"
#include <iostream>
#include <Platform.h>
#include "Client.h"
#include "FruitInfo.h"

ClientGame::ClientGame(){}

//Initializes GameObjects
void ClientGame::Init()
{    
    _gameObjects.reserve(3);
    
    InitPlayers();

    //Init fruit 
    _fruit = new ClientFruit(20, 5, TILE_PIXEL_SIZE, "bin/Assets/apple.bmp");
    _gameObjects.push_back(_fruit);
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
    
        ClientPlayer* player = new ClientPlayer(x, y, TILE_PIXEL_SIZE, "bin/Assets/Red.bmp");
        _gameObjects.push_back(player);
        _players.push_back(player);

        x = 5; y = 19;

        player = new ClientPlayer(x, y, TILE_PIXEL_SIZE, "bin/Assets/Blue.bmp");
        _gameObjects.push_back(player);
        _players.push_back(player);
    }
    else if(Client::GetID() == '1') //player 2
    {
        int x = 25; int y = 19;
    
        ClientPlayer* player = new ClientPlayer(x, y, TILE_PIXEL_SIZE, "bin/Assets/Blue.bmp");
        _gameObjects.push_back(player);
        _players.push_back(player);

        x = 5; y = 19;

        player = new ClientPlayer(x, y, TILE_PIXEL_SIZE, "bin/Assets/Red.bmp");
        _gameObjects.push_back(player);
        _players.push_back(player);

    }
    else
    {
        std::cout << "Error creating players\n";
    }
    
    
}

//Updates specific snake
void ClientGame::UpdatePlayerSnakeHead(Node* node, int player)
{
    _players[player]->SetHead(node);
}

//Adds node to specific snake
void ClientGame::AddNodeToSnake(Node* node, int player)
{
    _players[player]->AddNode(node);
}

//Relocates fruit when fruit has changed position
void ClientGame::FruitRellocated(FruitInfo* info)
{
    _fruit->SetNewPosition(info->x, info->y);
}

ClientGame::~ClientGame()
{
   //TODO: release players
   //TODO: releas fruit
}