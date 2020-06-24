#include "ClientPlayer.h"
#include <SDL2/SDL_image.h>
#include "Renderer.h"
#include "Node.h"

ClientPlayer::ClientPlayer(int x, int y, int size, const char* path) 
    : _xPos(x), _yPos(y), _size(size)
{
    int width, height;    
    _texture = Renderer::LoadImage(path, &width, &height); //load texture
    _srcRect = new SDL_Rect {0, 0, width, height}; //source texture rect

    _snake.push_back(new Node(x, y)); //head node
}

//Updates snake
void ClientPlayer::Update(){}

//Renders snake nodes
void ClientPlayer::Render()
{
    for(auto node : _snake)
    {
        SDL_Rect destRect = {node->x * _size, node->y * _size, _size, _size};
        SDL_RenderCopy(Renderer::GetRenderer(), _texture, _srcRect, &destRect);
    }
}

//Stores the head new position 
void ClientPlayer::SetHead(Node* head)
{
    _xPos = head->x; //store new head position
    _yPos = head->y;

    SetNewPosition(); //update position of full snake
}

//Adds node after tail
void ClientPlayer::AddNode(Node* node)
{
    Node* tail = node;
    //set father & next nodes 
    _snake.back()->next = tail;
    tail->father = _snake.back();
    tail->UpdateDirections();
    _snake.push_back(tail);    
}

//Sets all snake nodes in new position
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

ClientPlayer::~ClientPlayer()
{
    SDL_DestroyTexture(_texture);
    _texture =  nullptr;

    delete _srcRect;
    _srcRect = nullptr;

    //TODO: FREE NODE LIST 
}