#include "Fruit.h"
#include <SDL2/SDL_image.h>
#include "Renderer.h"
#include <iostream>
#include "Game.h"
#include "FruitInfo.h"

Fruit::Fruit(int x, int y, int size, const char* path) : _xPos(x), _yPos(y), _size(size)
{
    _type = GameObject::Fruit;   

    int width, height;    
    _texture = Renderer::LoadImage(path, &width, &height); //load texture
    _srcRect = new SDL_Rect {0, 0, width, height}; //source texture rect

}

void Fruit::Update(){}

//Renders fruit as tile in tilemap
void Fruit::Render()
{
    SDL_Rect destRect = {_xPos * _size, _yPos * _size, _size, _size};
    SDL_RenderCopy(Renderer::GetRenderer(), _texture, _srcRect, &destRect);
}

//When fruit is eaten, fruit changes position
FruitInfo Fruit::Rellocate(Game* g)
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

void Fruit::SetNewPosition(int x, int y, Game* g)
{
    _xPos = x; _yPos = y; //new fruit position
    Tile tile;
    tile.empty = false; tile.go = this;
    g->SetTile(x, y, tile);
}

Fruit::~Fruit()
{
    SDL_DestroyTexture(_texture);
    _texture =  nullptr;

    delete _srcRect;
    _srcRect = nullptr;
}