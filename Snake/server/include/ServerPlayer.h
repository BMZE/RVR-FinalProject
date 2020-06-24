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
    ServerPlayer(int x, int y, ServerGame* g, int playerID);
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

    /**
     * Sets new player input
     * @param info new input info collected by server
     */
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
    
    int _xPos = 0; //head node x & y position
    int _yPos = 0;

    int _playerID = 0; //Player 1 or Player 2

    Node::Direction _direction; //head direction

    std::list<Node*> _snake;

    ServerGame* _game = nullptr; //reference to game instance

    bool _collision = false;

    InputInfo _inputInfo;
};
#endif