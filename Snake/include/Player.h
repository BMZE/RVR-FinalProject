#ifndef _H_Player_H_
#define _H_Player_H_
#include <list>
#include <vector>
#include "GameObject.h"

class SDL_Texture;
class SDL_Rect;
class Node;

class Player : public GameObject
{
public:
    Player(int x, int y, int w, int h, const char* path, Type t);
    ~Player();

    /**
     * Updates snake
     */
    void Update(std::vector<std::vector<Tile*>> &tilemap);
    
    /**
     * Renders snake
     */
    void Render();

    inline Type GetType(){ return _type; };

private:

    /**
     * Handles input -> snake direction change
     */
    void Input();

    /**
     * Snake position update
     */
    void Move(std::vector<std::vector<Tile*>> &tilemap);

    bool OnCollision(std::vector<std::vector<Tile*>> &tilemap);

    void AddNode(int x, int y, std::vector<std::vector<Tile*>> &tilemap);

    void DisplayDir(); //debug method for current snake direction

    bool FindDuplicate(); //true if there are two snake nodes in one tile

    enum Direction {North, East, South, West}; //snake direction

    SDL_Texture* _texture; //image texture

    int _xPos; //head node position
    int _yPos;

    int _width; //node width & height in pixels
    int _height;
    
    SDL_Rect* _srcRect;
    Direction _direction;

    std::list<Node*> _snake;

    bool firstUpdate = false;
};


class Node
{
public:
    Node(int xP, int yP) :x(xP), y(yP){};
    ~Node(){};

    int x;
    int y;

    Node* father = nullptr;
    Node* next = nullptr; 

    //update pos from before method
    void UpdatePosition()
    {
        if(father != nullptr)
        {
            father->x = x;
            father->y = y;
        }
    };

};

#endif