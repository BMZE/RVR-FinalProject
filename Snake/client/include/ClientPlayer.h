#ifndef _H_ClientPlayer_H_
#define _H_ClientPlayer_H_
#include <list>
#include <vector>
#include "GameObject.h"
#include "InputInfo.h"
#include "Node.h"

//FORWARDS DECLARATIONS
class SDL_Texture;
class SDL_Rect;
class Node;
class ClientGame;

class ClientPlayer : public GameObject
{
public:
    ClientPlayer(int x, int y, int size, const char* path, bool player, ClientGame* g);
    ~ClientPlayer();

    /**
     * Updates snake
     */
    void Update();
    
    /**
     * Renders snake
     */
    void Render();

    /**
     * @return Type of GameObject (snake)
     */
    inline Type GetType(){ return _type; };

    void SetInputInfo(InputInfo* info);

    /**
     * Adds new node to the snake list with correct direction to follow
     */
    void AddNode(Node* tail); 

    void SetHead(Node* head);

    void SetNewPosition(); //Sets all snake nodes in new tile position


private:



    void Input(); //Handles input -> snake direction change

    void Move(); //Set head in new tile position

    void DirectionChange(); //called when snake changes direction, updates nodes current direction
    
    bool OnCollision(); //Checks snake's possible collisions

    void DisplayDir(); //debug method for current snake direction
    
    int _xPos; //head node x & y position
    int _yPos;
    int _size; //node width & height in pixels
    
    SDL_Rect* _srcRect; //texture source rect
    SDL_Texture* _texture; //image texture

    Node::Direction _direction; //head direction

    std::list<Node*> _snake;

    ClientGame* _game; //reference to game instance

    bool _collision = false;

    bool _player = false; //true if it's the player, false if other player

    InputInfo _inputInfo;
};
#endif