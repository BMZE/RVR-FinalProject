#include "Player.h"
#include <SDL2/SDL_image.h>
#include "Renderer.h"
#include <iostream>
#include "Input.h"
#include "InputInfo.h"

Player::Player(int x, int y, int w, int h, const char* path, Game* g) 
    : _xPos(x), _yPos(y), _width(w), _height(h)
{
    int width, height;    
    _texture = Renderer::LoadImage(path, &width, &height); //load texture
    _srcRect = new SDL_Rect {0, 0, width, height}; //source texture rect

    _direction = North; //initial direction

    _snake.push_back(new Node(x, y)); //head node

    _type = GameObject::Snake;
    
    _game = g; //game reference

    //Snake tile
    _snakeTile.empty = false;
    _snakeTile.go = this;
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

    _game->SetTile(x, y, _snakeTile); //set node info on tilemap
    
    std::cout << _snake.size() << '\n';
}

void Player::Update()
{
    if(!firstUpdate) //FOR DEBUGGING LONGER SNAKE
    {
        int x = _xPos; int y = _yPos;
        firstUpdate = true;
        y++; AddNode(x, y);
        y++; AddNode(x, y);
        y++; AddNode(x, y);
        y++; AddNode(x, y);
    }

    //std::cout << "TYPE: " << tilemap[_xPos][_yPos].go->GetType() << '\n';

    Input(); //handle input

    if(!_collision)
        Move(); //next snake pos

    //check if next is out of bounds && check new pos' collisions
    if(!OutOfBounds() && !OnCollision()) 
    {   
        SetNewPosition(); //update snake to new pos
    }
    else 
    {
        _collision = true;
    }
}

//Returns true if snake gets out of bounds (the window)
bool Player::OutOfBounds()
{
    if(_xPos < 0 || _xPos >= _game->GetTilemap().size()
        || _yPos < 0 || _yPos >= _game->GetTilemap()[0].size())
    {
        printf("OUT OF BOUNDS\n");
        return true;
    }  

    return false; 
}

bool Player::OnCollision()
{   
    if(!_game->GetTilemap()[_xPos][_yPos].empty
        && _game->GetTilemap()[_xPos][_yPos].go->GetType() == GameObject::Snake) 
    {
        std::cout << "COLLISION WITH SNAKE\n"; //stops snake
        return true;
    }
    else if(!_game->GetTilemap()[_xPos][_yPos].empty 
         && _game->GetTilemap()[_xPos][_yPos].go->GetType() == GameObject::Fruit) //collision with fruit
    {
        _game->FruitEaten(_xPos, _yPos);

        int y = _snake.back()->y;
        y++; AddNode(_xPos, y);
        
        std::cout << "COLLISION WITH FRUIT\n"; //dows not stop snake
        return false;
    }   

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

void Player::SetNewPosition()
{
     Node* it = _snake.back(); 
     
     _game->SetTile(it->x, it->y, Tile()); //reset old tail info on tilemap 

    if(_snake.size() > 1) //snake has more than one node
    {   
        while(it->father != nullptr) //Update nodes
        {
            it->x = it->father->x;
            it->y = it->father->y;
            it = it->father;
        }
    }

    //head new position
    _snake.front()->x = _xPos; 
    _snake.front()->y = _yPos;

    _game->SetTile(_xPos,_yPos, _snakeTile); //head new tile
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

    //TODO: FREE NODE LIST 
}


//Displays direction for debugging
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
