#include "ClientPlayer.h"
#include <SDL2/SDL_image.h>
#include "Renderer.h"
#include <iostream>
#include "Input.h"
#include "InputInfo.h"
#include "ClientGame.h"
#include "Client.h"

ClientPlayer::ClientPlayer(int x, int y, int size, const char* path, bool player, ClientGame* g) 
    : _xPos(x), _yPos(y), _size(size), _player(player)
{
    int width, height;    
    _texture = Renderer::LoadImage(path, &width, &height); //load texture
    _srcRect = new SDL_Rect {0, 0, width, height}; //source texture rect

    _direction = Node::North; //initial direction

    _snake.push_back(new Node(x, y)); //head node

    _type = GameObject::Snake; 
    
    _game = g; //game reference

}

//Updates snake
void ClientPlayer::Update()
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
void ClientPlayer::Render()
{
    for(auto node : _snake)
    {
        SDL_Rect destRect = {node->x * _size, node->y * _size, _size, _size};
        SDL_RenderCopy(Renderer::GetRenderer(), _texture, _srcRect, &destRect);
    }
}

//Handles input -> snake direction change
void ClientPlayer::Input()
{   
    // if(_player)
    //     _inputInfo = Input::GetInputInfo();
    
    // bool newDir = false;

    // if (_inputInfo.right && (_direction == Node::North || _direction == South)) //right
    // {
    //     _direction = East;
    //     newDir = true; 
    // }
    // else if(_inputInfo.left && (_direction == North || _direction == South)) //left
    // {
    //     _direction = West;
    //     newDir = true; 
    // }
    // else if(_inputInfo.forward && (_direction == West || _direction == East)) //up
    // {
    //     _direction = North;
    //     newDir = true; 
    // }
    // else if(_inputInfo.back && (_direction == West || _direction == East)) //down
    // {
    //     _direction = South;
    //     newDir = true; 
    // }

    // if(newDir)
    // {
    //     if(_player)
    //         Client::SendInput(_inputInfo); //Send new dir over network
    //     else
    //         _inputInfo = InputInfo(); //reset inputinfo
        
    //     DirectionChange();
    //    // DisplayDir();
    // }
}

void ClientPlayer::SetInputInfo(InputInfo* info)
{
    _inputInfo = *info;
}

//Checks snake's possible collisions
bool ClientPlayer::OnCollision()
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
       // AddNode();

       // std::cout << "COLLISION WITH FRUIT\n"; //dows not stop snake
        return false;
    }   

    return false;
}

#pragma region SNAKE NODE MANAGEMENT

void ClientPlayer::SetHead(Node* head)
{
    _xPos = head->x;
    _yPos = head->y;

    _snake.front()->lastDirecion = head->lastDirecion; //front new direction
    _snake.front()->currentDirection = head->currentDirection;
}

//Called when snake changes direction, updates nodes current direction
void ClientPlayer::DirectionChange()
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
void ClientPlayer::AddNode(Node* node)
{
    Node* tail = node;
    //set father & next nodes 
    _snake.back()->next = tail;
    tail->father = _snake.back();
    tail->UpdateDirections();
    _snake.push_back(tail);    
}

//Set head in new tile position 
void ClientPlayer::Move()
{
    // switch (_direction)
    // {
    //     case North:
    //         _yPos--;
    //         break;
    //     case South:
    //         _yPos++;
    //         break;
    //     case West:
    //         _xPos--;
    //         break;
    //     case East:
    //         _xPos++;
    //         break;
    //     default:
    //         break;
    // }   
}

//Sets all snake nodes in new tile position
void ClientPlayer::SetNewPosition()
{
     Node* it = _snake.back(); 
     
    if(_snake.size() > 1) //snake has more than one node
    {   
        while(it->father != nullptr) //Update nodes
        {
            it->UpdatePosition();
            it = it->father;
        }
    }

    //head new position
    _snake.front()->x = _xPos; 
    _snake.front()->y = _yPos;
}

#pragma endregion

ClientPlayer::~ClientPlayer()
{
    SDL_DestroyTexture(_texture);
    _texture =  nullptr;

    delete _srcRect;
    _srcRect = nullptr;

    //TODO: FREE NODE LIST 
}

//Displays direction for debugging
void ClientPlayer::DisplayDir()
{
    // std::string dir = "";
    // switch (_direction)
    // {
    //     case North:
    //     dir = "NORTH";
    //         break;
    //     case South:
    //     dir = "SOUTH";
    //         break;
    //     case West:
    //     dir = "WEST"; 
    //         break;
    //     case East:
    //     dir = "EAST"; 
    //         break;
    //     default:
    //         break;
    // }

    // std::cout << dir << '\n';
}
