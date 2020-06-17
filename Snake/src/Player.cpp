#include "Player.h"
#include <SDL2/SDL_image.h>
#include "Renderer.h"
#include <iostream>
#include "Input.h"
#include "InputInfo.h"
#include "Game.h"
#include "Client.h"

Player::Player(int x, int y, int size, const char* path, bool player, Game* g) 
    : _xPos(x), _yPos(y), _size(size), _player(player)
{
    int width, height;    
    _texture = Renderer::LoadImage(path, &width, &height); //load texture
    _srcRect = new SDL_Rect {0, 0, width, height}; //source texture rect

    _direction = North; //initial direction

    _snake.push_back(new Node(x, y)); //head node

    _type = GameObject::Snake; 
    
    _game = g; //game reference

}

//Updates snake
void Player::Update()
{
    Input(); //handle input

    if(!_collision) //collision impends snake movement
    {
        Move(); //next snake pos
        if(!OnCollision()) //if next tile is available for movement
            SetNewPosition(); //set snake to next tile
    }   
}

//Renders snake nodes
void Player::Render()
{
    for(auto node : _snake)
    {
        SDL_Rect destRect = {node->x * _size, node->y * _size, _size, _size};
        SDL_RenderCopy(Renderer::GetRenderer(), _texture, _srcRect, &destRect);
    }
}

//Handles input -> snake direction change
void Player::Input()
{   
    if(_player)
        _inputInfo = Input::GetInputInfo();
    
    bool newDir = false;

    if (_inputInfo.right && (_direction == North || _direction == South)) //right
    {
        _direction = East;
        newDir = true; 
    }
    else if(_inputInfo.left && (_direction == North || _direction == South)) //left
    {
        _direction = West;
        newDir = true; 
    }
    else if(_inputInfo.forward && (_direction == West || _direction == East)) //up
    {
        _direction = North;
        newDir = true; 
    }
    else if(_inputInfo.back && (_direction == West || _direction == East)) //down
    {
        _direction = South;
        newDir = true; 
    }

    if(newDir)
    {
        if(_player)
            Client::SendInput(_inputInfo); //Send new dir over network
        else
            _inputInfo = InputInfo(); //reset inputinfo
        
        DirectionChange();
       // DisplayDir();
    }
}

void Player::SetInputInfo(InputInfo* info)
{
    _inputInfo = *info;
}

//Checks snake's possible collisions
bool Player::OnCollision()
{   
    if(_xPos < 0 || _xPos >= _game->GetTilemap().size()
        || _yPos < 0 || _yPos >= _game->GetTilemap()[0].size()) //Out of bounds collision
    {
        //printf("OUT OF BOUNDS\n");
        _collision = true; //snake collided
        return true;
    }  
    else if(!_game->GetTilemap()[_xPos][_yPos].empty
        && _game->GetTilemap()[_xPos][_yPos].go->GetType() == GameObject::Snake) //collision with snake
    {
        //std::cout << "COLLISION WITH SNAKE\n"; //stops snake
        _collision = true; //snake collided
        return true;
    }
    //if not acting as playing player, but server player, fruit collision should not be handled
    //TODO: not call collisions unles player
    else if(_player && !_game->GetTilemap()[_xPos][_yPos].empty 
         && _game->GetTilemap()[_xPos][_yPos].go->GetType() == GameObject::Fruit) //collision with fruit
    {
        _game->FruitEaten(_xPos, _yPos);
        AddNode();

       // std::cout << "COLLISION WITH FRUIT\n"; //dows not stop snake
        return false;
    }   

    return false;
}

#pragma region SNAKE NODE MANAGEMENT

//Called when snake changes direction, updates nodes current direction
void Player::DirectionChange()
{
    _snake.front()->lastDirecion = _snake.front()->currentDirection; //front new direction
    _snake.front()->currentDirection = _direction;

    if(_snake.size() > 1) //update rest of nodes direction 
    {
        Node* it = _snake.front()->next;
        while(it->next != nullptr)
        {
            it->UpdateDirections();
            it = it->next;
        }
    }
}

//Adds node after tail with correct direction to follow
void Player::AddNode()
{
    int x = 0; int y = 0;
    
    //New node position (after tail)
    if(_snake.back()->lastDirecion == North)
    {
        x = _snake.back()->x; y = _snake.back()->y + 1;
    }
    else if(_snake.back()->lastDirecion == South)
    {
        x = _snake.back()->x; y = _snake.back()->y - 1;
    }
    else if(_snake.back()->lastDirecion == West)
    {
        x = _snake.back()->x - 1; y = _snake.back()->y;
    }
    else if(_snake.back()->lastDirecion == East)
    {
        x = _snake.back()->x + 1; y = _snake.back()->y;
    }

    Node* node = new Node(x, y);

    //set father & next nodes 
    _snake.back()->next = node; //TODO: SNAKE.BACK()
    node->father = _snake.back();
    node->UpdateDirections();
    _snake.push_back(node);

    //Snake tile
    Tile tile;
    tile.empty = false; tile.go = this;
    
    _game->SetTile(x, y, tile); //set node info on tilemap
    
   // std::cout << _snake.size() << '\n';
}

//Set head in new tile position 
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

//Sets all snake nodes in new tile position
void Player::SetNewPosition()
{
     Node* it = _snake.back(); 
     
     _game->SetTile(it->x, it->y, Tile()); //reset old tail info on tilemap 

    if(_snake.size() > 1) //snake has more than one node
    {   
        while(it->father != nullptr) //Update nodes
        {
            // it->x = it->father->x;
            // it->y = it->father->y;
            it->UpdatePosition();
            it = it->father;
        }
    }

    //head new position
    _snake.front()->x = _xPos; 
    _snake.front()->y = _yPos;

    //Snake tile
    Tile tile;
    tile.empty = false; tile.go = this;

    _game->SetTile(_xPos,_yPos, tile); //head new tile
}

#pragma endregion

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
