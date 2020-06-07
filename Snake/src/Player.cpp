#include "Player.h"
#include <SDL2/SDL_image.h>
#include "Renderer.h"
#include <iostream>
#include "Input.h"
#include "InputInfo.h"

Player::Player(int x, int y, int w, int h, const char* path): _xPos(x), _yPos(y), _width(w), _height(h)
{
    int width, height;    
    _texture = Renderer::LoadImage(path, &width, &height);

    _srcRect = new SDL_Rect {0, 0, width, height}; //source texture rect

    _direction = North;
}



void Player::Update()
{
    Input();

    Move();

    
}

void Player::Render()
{
    SDL_Rect destRect = {_xPos, _yPos, _width, _height};
    SDL_RenderCopy(Renderer::GetRenderer(), _texture, _srcRect, &destRect);
}

void Player::Input()
{
    InputInfo info = Input::GetInputInfo();
    
    if (info.right)
    {
        int aux = _direction;
        aux++;
        if(aux >= END)
            aux = 0;
        _direction = (Direction)aux;
        std::cout << "Direction: " << _direction <<'\n';
    }
    else if(info.left)
    {
        int aux = _direction;
        aux--;
        if(aux < 0)
            aux = (int)END - 1;
        _direction = (Direction)aux;
        std::cout << "Direction: " << _direction <<'\n';
    }
}


void Player::Move()
{
    switch (_direction)
        {
        case North:
            _yPos--;
            break;
        case South:
            _yPos++;
            break;
        case West:
            _xPos--;
            break;
        case East:
            _xPos++;
            break;
        default:
            break;
        }
}

Player::~Player()
{
    SDL_DestroyTexture(_texture);
    _texture =  nullptr;

    delete _srcRect;
    _srcRect = nullptr;
}

