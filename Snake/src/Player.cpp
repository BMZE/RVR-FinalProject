#include "Player.h"
#include <SDL2/SDL_image.h>
#include "Renderer.h"


Player::Player(int x, int y, const char* path)
{
    _xPos = x;
    _yPos = y;
    _texture = Renderer::LoadImage(path);
}

void Player::Render()
{
    SDL_RenderCopy(Renderer::GetRenderer(), _texture, nullptr, nullptr);
}

Player::~Player()
{
    SDL_DestroyTexture(_texture);
    _texture =  nullptr;
}

