#include "ClientFruit.h"
#include <SDL2/SDL_image.h>
#include "Renderer.h"

ClientFruit::ClientFruit(int x, int y, int size, const char* path) 
    : _xPos(x), _yPos(y), _size(size)
{
    int width, height;    
    _texture = Renderer::LoadImage(path, &width, &height); //load texture
    _srcRect = new SDL_Rect {0, 0, width, height}; //source texture rect

}

void ClientFruit::Update(){}

//Renders fruit depending on tile size
void ClientFruit::Render()
{
    SDL_Rect destRect = {_xPos * _size, _yPos * _size, _size, _size};
    SDL_RenderCopy(Renderer::GetRenderer(), _texture, _srcRect, &destRect);
}

//Sets fruit position
void ClientFruit::SetNewPosition(int x, int y)
{
    _xPos = x; _yPos = y; //new fruit position
}

ClientFruit::~ClientFruit()
{
    SDL_DestroyTexture(_texture);
    _texture =  nullptr;

    delete _srcRect;
    _srcRect = nullptr;
}