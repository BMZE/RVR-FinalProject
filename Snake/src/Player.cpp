#include "Player.h"
#include <SDL2/SDL_image.h>
#include "Renderer.h"
#include <iostream>
#include "Input.h"
#include "InputInfo.h"

Player::Player(int x, int y, int w, int h, const char* path, Type t) 
    : _xPos(x), _yPos(y), _width(w), _height(h)
{
    int width, height;    
    _texture = Renderer::LoadImage(path, &width, &height); //load texture
    _srcRect = new SDL_Rect {0, 0, width, height}; //source texture rect

    _direction = North; //initial direction

    _snake.push_back(new Node(x, y)); //head node

    _type = t;
}

void Player::AddNode(int x, int y, std::vector<std::vector<Tile*>> &tilemap)
{
    Node* node = new Node(x, y);
    
    Node* it = _snake.front();
    while(it->next != nullptr)
        it = it->next;
    
    it->next = node;
    node->father = it;
    _snake.push_back(node);

    tilemap[x][y]->go = this;
    tilemap[x][y]->empty = false;
    
    std::cout << _snake.size() << '\n';
}

void Player::Update(std::vector<std::vector<Tile*>> &tilemap)
{
    if(!firstUpdate)
    {
        int x = _xPos; int y = _yPos;
        firstUpdate = true;
        y++; AddNode(x, y, tilemap);
        y++; AddNode(x, y, tilemap);
        y++; AddNode(x, y, tilemap);
        y++; AddNode(x, y, tilemap);
        //y++; AddNode(x, y, tilemap);
        // y++; AddNode(x, y, tilemap);            
        // y++; AddNode(x, y, tilemap);
    }

    Input();

    Move(tilemap); 

    OnCollision(tilemap);
}

bool Player::OnCollision(std::vector<std::vector<Tile*>> &tilemap)
{
    //Out of bounds collision
    if(_xPos < 0 || _xPos >= tilemap.size())
        return true;
    else if(_yPos < 0 || _yPos >= tilemap[0].size())
        return true;
    else if(!tilemap[_xPos][_yPos]->empty && FindDuplicate())
    {
        std::cout << "COLLISION WITH SNAKE\n";
        return true;
    }
    // else if(!tilemap[_xPos][_yPos]->empty 
    //     && tilemap[_xPos][_yPos]->go->GetType() == GameObject::Fruit) //collision with fruit
    //     

    return false;
}

bool Player::FindDuplicate()
{
    Node* it = _snake.front();
    while(it->next != nullptr)
    {    
        it = it->next;
        if(_xPos == it->x && _yPos == it->y)
            return true;
    }

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


void Player::Move(std::vector<std::vector<Tile*>> &tilemap)
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

    Node* it = _snake.back(); //old tail node is free in tilemap
    tilemap[it->x][it->y]->empty = true;
    tilemap[it->x][it->y]->go = nullptr;

    if(_snake.size() > 1) //snake has more than one node
    {   
        while(it->father != nullptr)
        {
            it->x = it->father->x;
            it->y = it->father->y;
            it = it->father;
        }
    }
    _snake.front()->x = _xPos;
    _snake.front()->y = _yPos;

    tilemap[_xPos][_yPos]->empty = false;
    tilemap[_xPos][_yPos]->go = this;
}

Player::~Player()
{
    SDL_DestroyTexture(_texture);
    _texture =  nullptr;

    delete _srcRect;
    _srcRect = nullptr;

    //TODO: FREE NODE LIST 
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
            break;
    }

    std::cout << dir << '\n';
}
