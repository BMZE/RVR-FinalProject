#ifndef _H_Player_H_
#define _H_Player_H_
#include <list>
#include <vector>

class SDL_Texture;
class SDL_Rect;
class Node;

class Player 
{
public:
    Player(int x, int y, int w, int h, const char* path);
    ~Player();

    /**
     * Updates snake
     */
    void Update(std::vector<std::vector<bool>> &tilemap);
    
    /**
     * Renders snake
     */
    void Render();

private:

    /**
     * Handles input -> snake direction change
     */
    void Input();

    /**
     * Snake position update
     */
    void Move();

    bool OnCollision(std::vector<std::vector<bool>> &tilemap);

    void AddNode(int x, int y);

    void DisplayDir(); //debug method for current snake direction

    enum Direction {North, East, South, West}; //snake direction

    SDL_Texture* _texture; //image texture

    int _xPos; //head node position
    int _yPos;

    int _width; //node width & height in pixels
    int _height;
    
    SDL_Rect* _srcRect;
    Direction _direction;

    std::list<Node*> _snake;
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