#include "ServerFruit.h"
#include "ServerGame.h"
#include <iostream>

ServerFruit::ServerFruit(int x, int y)
{
    _type = GameObject::Fruit;
    _position.x = x;
    _position.y = y;
}

void ServerFruit::Update(){}

void ServerFruit::Render(){}

//When fruit is eaten, fruit changes position
FruitInfo ServerFruit::Rellocate(ServerGame* g)
{
    while(true)
    {
        //random pos
        int x = rand() % g->GetTilemap().size();
        int y = rand() % g->GetTilemap()[0].size();

        //if tile is free and not the same as current
        if((x != _position.x && y != _position.y) && g->GetTilemap()[x][y].empty) 
        {
            SetNewPosition(x, y, g);      
            //SEND NEW FRUIT POS
            return _position;
        }
    }
}

FruitInfo ServerFruit::GetPosition()
{
    return _position; 
}

void ServerFruit::SetNewPosition(int x, int y, ServerGame* g)
{
    _position.x = x; _position.y = y; //new fruit position
    Tile tile;
    tile.empty = false; tile.go = this;
    g->SetTile(x, y, tile);
}

ServerFruit::~ServerFruit()
{

}