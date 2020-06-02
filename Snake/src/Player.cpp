#include "Player.h"
#include <SDL2/SDL_image.h>
#include "Renderer.h"
#include <iostream>

Player::Player(int x, int y, int w, int h, const char* path): _xPos(x), _yPos(y), _width(w), _height(h)
{
    int width, height;    
    _texture = Renderer::LoadImage(path, &width, &height);

    _srcRect = new SDL_Rect {0, 0, width, height}; //source texture rect
}

void Player::Render()
{
    SDL_Rect destRect = {_xPos, _yPos, _width, _height};
    SDL_RenderCopy(Renderer::GetRenderer(), _texture, _srcRect, &destRect);
}

Player::~Player()
{
    SDL_DestroyTexture(_texture);
    _texture =  nullptr;

    delete _srcRect;
    _srcRect = nullptr;
}

