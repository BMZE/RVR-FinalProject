#include "ClientFruit.h"
#include <SDL2/SDL_image.h>
#include "Renderer.h"
#include <iostream>
#include "ClientGame.h"
#include "FruitInfo.h"

ClientFruit::ClientFruit(int x, int y, int size, const char* path) : _xPos(x), _yPos(y), _size(size)
{
    _type = GameObject::Fruit;   

    int width, height;    
    _texture = Renderer::LoadImage(path, &width, &height); //load texture
    _srcRect = new SDL_Rect {0, 0, width, height}; //source texture rect

}

void ClientFruit::Update(){}

//Renders fruit as tile in tilemap
void ClientFruit::Render()
{
    SDL_Rect destRect = {_xPos * _size, _yPos * _size, _size, _size};
    SDL_RenderCopy(Renderer::GetRenderer(), _texture, _srcRect, &destRect);
}

//When fruit is eaten, fruit changes position
FruitInfo ClientFruit::Rellocate(ClientGame* g)
{
    while(true)
    {
        //random pos
        int x = rand() % g->GetTilemap().size();
        int y = rand() % g->GetTilemap()[0].size();

        //if tile is free and not the same as current
        if((x != _xPos && y != _yPos) && g->GetTilemap()[x][y].empty) 
        {
            SetNewPosition(x, y, g);   
            FruitInfo info; 
            info.x = x; info.y = y;   
            return info;
        }
    }
}

FruitInfo ClientFruit::GetPosition()
{
    FruitInfo info; 
    info.x = _xPos; info.y = _yPos;
    return info; 
}

void ClientFruit::SetNewPosition(int x, int y, ClientGame* g)
{
    _xPos = x; _yPos = y; //new fruit position
    Tile tile;
    tile.empty = false; tile.go = this;
    g->SetTile(x, y, tile);
}

ClientFruit::~ClientFruit()
{
    SDL_DestroyTexture(_texture);
    _texture =  nullptr;

    delete _srcRect;
    _srcRect = nullptr;
}