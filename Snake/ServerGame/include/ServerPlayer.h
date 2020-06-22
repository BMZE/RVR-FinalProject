#ifndef _H_Player_H_
#define _H_Player_H_
#include <list>
#include <vector>
#include "GameObject.h"
#include "InputInfo.h"
#include "Node.h"

//FORWARDS DECLARATIONS
class ServerGame;

class ServerPlayer : public GameObject
{
public:
    ServerPlayer(int x, int y, ServerGame* g);
    ~ServerPlayer();

    /**
     * Updates snake
     */
    void Update();

    void Render(){}; //not used in server

    /**
     * @return Type of GameObject (snake)
     */
    inline Type GetType(){ return _type; };

    void SetInputInfo(InputInfo* info);

    /**
     * Adds new node to the snake list with correct direction to follow
     */
    void AddNode(); 

private:

    void Input(); //Handles input -> snake direction change

    void Move(); //Set head in new tile position

    void DirectionChange(); //called when snake changes direction, updates nodes current direction

    void SetNewPosition(); //Sets all snake nodes in new tile position
    
    bool OnCollision(); //Checks snake's possible collisions

    void DisplayDir(); //debug method for current snake direction
    
    int _xPos; //head node x & y position
    int _yPos;
    int _size; //node width & height in pixels

    Node::Direction _direction; //head direction

    std::list<Node*> _snake;

    ServerGame* _game; //reference to game instance

    bool _collision = false;

    InputInfo _inputInfo;
};
#endif