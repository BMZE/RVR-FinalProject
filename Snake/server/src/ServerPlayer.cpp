#include "ServerPlayer.h"
#include <iostream>
// #include "Input.h"
#include "InputInfo.h"
#include "ServerGame.h"
#include "Message.h"

ServerPlayer::ServerPlayer(int x, int y, ServerGame* g, int playerID) 
    : _xPos(x), _yPos(y), _playerID(playerID)
{
    _direction = Node::North; //initial direction

    _snake.push_back(new Node(x, y)); //head node

    _type = GameObject::Snake; 
    
    _game = g; //ServerGame reference
}

//Updates snake
void ServerPlayer::Update()
{
    if(!_collision) //collision impends snake movement
    {
        Input(); //handle input

        Move(); //next snake pos
        if(!OnCollision()) //if next tile is available for movement
            SetNewPosition(); //set snake to next tile
    }   
}

//Handles input -> snake direction change
void ServerPlayer::Input()
{   
    bool newDir = false;

    if (_inputInfo.right && (_direction == Node::North || _direction == Node::South)) //right
    {
        _direction = Node::East;
        newDir = true; 
    }
    else if(_inputInfo.left && (_direction == Node::North || _direction == Node::South)) //left
    {
        _direction = Node::West;
        newDir = true; 
    }
    else if(_inputInfo.forward && (_direction == Node::West || _direction == Node::East)) //up
    {
        _direction = Node::North;
        newDir = true; 
    }
    else if(_inputInfo.back && (_direction == Node::West || _direction == Node::East)) //down
    {
        _direction = Node::South;
        newDir = true; 
    }

    if(newDir)
    {   
        DirectionChange();
       // DisplayDir();
    }
}

//Sets new player input
void ServerPlayer::SetInputInfo(InputInfo* info)
{
    _inputInfo = *info;
}

//Checks snake's possible collisions
bool ServerPlayer::OnCollision()
{   
    if(_xPos < 0 || _xPos >= _game->GetTilemap().size()
        || _yPos < 0 || _yPos >= _game->GetTilemap()[0].size()) //Out of bounds collision
    {
       // printf("OUT OF BOUNDS\n");
        _collision = true; //snake collided
        return true;
    }  
    else if(_game->GetTilemap()[_xPos][_yPos] != nullptr
        && _game->GetTilemap()[_xPos][_yPos]->GetType() == GameObject::Snake) //collision with snake
    {
        //std::cout << "COLLISION WITH SNAKE\n"; //stops snake
        _collision = true; //snake collided
        return true;
    }
    else if(_game->GetTilemap()[_xPos][_yPos] != nullptr 
         && _game->GetTilemap()[_xPos][_yPos]->GetType() == GameObject::Fruit) //collision with fruit
    {
        _game->FruitEaten(_xPos, _yPos);
        AddNode();

       //std::cout << "COLLISION WITH FRUIT\n"; //dows not stop snake
        return false;
    }   

    return false;
}

#pragma region SNAKE NODE MANAGEMENT

//Called when snake changes direction, updates nodes current direction
void ServerPlayer::DirectionChange()
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
void ServerPlayer::AddNode()
{
    int x = 0; int y = 0;
    
    //New node position (after tail)
    if(_snake.back()->lastDirecion == Node::North)
    {
        x = _snake.back()->x; y = _snake.back()->y + 1;
    }
    else if(_snake.back()->lastDirecion == Node::South)
    {
        x = _snake.back()->x; y = _snake.back()->y - 1;
    }
    else if(_snake.back()->lastDirecion == Node::West)
    {
        x = _snake.back()->x - 1; y = _snake.back()->y;
    }
    else if(_snake.back()->lastDirecion == Node::East)
    {
        x = _snake.back()->x + 1; y = _snake.back()->y;
    }

    Node* node = new Node(x, y);

    //set father & next nodes 
    _snake.back()->next = node;
    node->father = _snake.back();
    node->UpdateDirections();
    _snake.push_back(node);

    //Snake tile
    _game->SetTile(x, y, this); //set node info on tilemap
    
   _game->SendToClients(Message(Message::ADD_NODE, _snake.back(), (_playerID + '0')));
}

//Set head in new tile position 
void ServerPlayer::Move()
{
    switch (_direction)
    {
        case Node::North:
            _yPos--;
            break;
        case Node::South:
            _yPos++;
            break;
        case Node::West:
            _xPos--;
            break;
        case Node::East:
            _xPos++;
            break;
        default:
            break;
    }   
}

//Sets all snake nodes in new tile position
void ServerPlayer::SetNewPosition()
{
     Node* it = _snake.back(); 
     
     _game->SetTile(it->x, it->y, nullptr); //reset old tail info on tilemap 

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

    //Snake tile
    _game->SetTile(_xPos,_yPos, this); //head new tile
    _game->SendToClients(Message(Message::NODE, _snake.front(), (_playerID + '0')));
}

#pragma endregion

ServerPlayer::~ServerPlayer()
{
    //delete allocated memory in node list 
    for(std::list<Node*>::const_iterator it = _snake.begin(); it != _snake.end(); it++)
    {
        delete *it;
    } 
    _snake.clear();
}

//Displays direction for debugging
void ServerPlayer::DisplayDir()
{
    std::string dir = "";
    switch (_direction)
    {
        case Node::North:
        dir = "NORTH";
            break;
        case Node::South:
        dir = "SOUTH";
            break;
        case Node::West:
        dir = "WEST"; 
            break;
        case Node::East:
        dir = "EAST"; 
            break;
        default:
            break;
    }

    std::cout << dir << '\n';
}
