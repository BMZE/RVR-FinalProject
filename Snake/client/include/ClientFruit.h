#ifndef _H_ClientFruit_H_
#define _H_ClientFruit_H_

#include "GameObject.h" 

//FORWARD DECLARATIONS
class SDL_Texture;
class SDL_Rect;
class ClientGame;
class FruitInfo;

class ClientFruit : public GameObject 
{
public:

    ClientFruit(int x, int y, int size, const char* path);
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
     * @return Type of GameObject (snake/fruit/...)
     */
    inline Type GetType(){ return _type; };

    /**
     * When fruit is eaten, fruit changes position
     */
    FruitInfo Rellocate(ClientGame* g);

    FruitInfo GetPosition();

    void SetNewPosition(int x, int y, ClientGame* g);
    
private:

    

    int _xPos; //position in tilemap
    int _yPos;
    int _size; //size in pixels

    SDL_Rect* _srcRect; //texture source rect
    SDL_Texture* _texture; //image texture

};
#endif