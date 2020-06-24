#ifndef _H_ClientPlayer_H_
#define _H_ClientPlayer_H_
#include <list>
#include <vector>
#include "GameObject.h"

//FORWARDS DECLARATIONS
class SDL_Texture;
class SDL_Rect;
class Node;

class ClientPlayer : public GameObject
{
public:

    /**
     * @param x coordinate X
     * @param y coordinate Y
     * @param path file path for loading image
     */
    ClientPlayer(int x, int y, int size, const char* path);

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

    /**
     * Adds new node to the snake
     * @param tail node to add 
     */
    void AddNode(Node* tail); 

    /**
     * Stores the head new position 
     * @param head snake front
     */
    void SetHead(Node* head);

    /**
     * Sets all snake nodes in new tile position
     */
    void SetNewPosition(); 


private:
    
    int _xPos; //head node x & y position
    int _yPos;
    int _size; //node width & height in pixels
    
    SDL_Rect* _srcRect; //texture source rect
    SDL_Texture* _texture; //image texture

    std::list<Node*> _snake;
};
#endif