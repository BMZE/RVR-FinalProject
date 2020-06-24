#ifndef _H_ClientFruit_H_
#define _H_ClientFruit_H_

#include "GameObject.h" 

//FORWARD DECLARATIONS
class SDL_Texture;
class SDL_Rect;

class ClientFruit : public GameObject 
{
public:

    /**
     * @param x coordinate X
     * @param y coordinate Y
     * @param size render size for texture
     * @param path file path for loading texture
     */
    ClientFruit(int x, int y, int size, const char* path);

    /**
     * Destroy resources
     */
    ~ClientFruit();

    /**
     * Updates GameObject
     */
    void Update();

    /**
     * Renders GameObject
     */
    void Render();

    /**
     * Sets fruit position
     * @param x X coordinate
     * @param y Y coordinate
     */
    void SetNewPosition(int x, int y);

    /**
     * @return Type of GameObject (fruit)
     */
    inline Type GetType(){ return _type; };
    
private:

    

    int _xPos; //position in tilemap
    int _yPos;
    int _size; //size in pixels

    SDL_Rect* _srcRect; //texture source rect
    SDL_Texture* _texture; //image texture

};
#endif