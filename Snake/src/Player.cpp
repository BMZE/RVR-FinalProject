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

    _snake.push_back(new Node(x, y)); //head nodes

    y++; AddNode(x, y);
    y++; AddNode(x, y);
    y++; AddNode(x, y);
    y++; AddNode(x, y);
    y++; AddNode(x, y);
    y++; AddNode(x, y);            
    y++; AddNode(x, y);

}

void Player::AddNode(int x, int y)
{
    Node* node = new Node(x, y);
    
    Node* it = _snake.front();
    while(it->next != nullptr)
        it = it->next;
    
    it->next = node;
    node->father = it;
    _snake.push_back(node);

    std::cout << _snake.size() << '\n';
}



void Player::Update(std::vector<std::vector<bool>> &tilemap)
{
    Input();

    Move(); 

    OnCollision(tilemap);
}

bool Player::OnCollision(std::vector<std::vector<bool>> &tilemap)
{
    //Out of bounds collision
    if(_xPos < 0 || _xPos >= tilemap.size())
        return true;
    else if(_yPos < 0 || _yPos >= tilemap[0].size())
        return true;
    else if(tilemap[_xPos][_yPos]) //collision with snake
        return true;

    return false;
}

void Player::Render()
{

    for(auto node : _snake)
    {
        SDL_Rect destRect = {node->x * 20, node->y * 20, _width, _height};
        SDL_RenderCopy(Renderer::GetRenderer(), _texture, _srcRect, &destRect);
    }
}

void Player::Input()
{
    InputInfo info = Input::GetInputInfo();
    
    if (info.right && (_direction == North || _direction == South)) //right
    {
        _direction = East;
        DisplayDir();
    }
    else if(info.left && (_direction == North || _direction == South)) //left
    {
        _direction = West;
        DisplayDir();
    }
    else if(info.forward && (_direction == West || _direction == East)) //up
    {
        _direction = North;
        DisplayDir();
    }
    else if(info.back && (_direction == West || _direction == East)) //down
    {
        _direction = South;
        DisplayDir();
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

    Node* it = _snake.back();
    
    while(it->father != nullptr)
    {
        it->x = it->father->x;
        it->y = it->father->y;
        it = it->father;
    }

    _snake.front()->x = _xPos;
    _snake.front()->y = _yPos;
}

Player::~Player()
{
    SDL_DestroyTexture(_texture);
    _texture =  nullptr;

    delete _srcRect;
    _srcRect = nullptr;
}

void Player::DisplayDir()
{
    std::string dir = "";
    switch (_direction)
    {
        case North:
        dir = "NORTH";
            break;
        case South:
        dir = "SOUTH";
            break;
        case West:
        dir = "WEST"; 
            break;
        case East:
        dir = "EAST"; 
            break;
        default:
        dir = "END";
            break;
    }

    std::cout << dir << '\n';
}
