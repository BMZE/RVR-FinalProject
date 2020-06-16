#ifndef _H_Fruit_H_
#define _H_Fruit_H_

#include "GameObject.h" 

//FORWARD DECLARATIONS
class SDL_Texture;
class SDL_Rect;
class Game;
class FruitInfo;

class Fruit : public GameObject 
{
public:

    Fruit(int x, int y, int size, const char* path);
    ~Fruit();

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
    FruitInfo Rellocate(Game* g);

    FruitInfo GetPosition();

    void SetNewPosition(int x, int y, Game* g);
    
private:

    

    int _xPos; //position in tilemap
    int _yPos;
    int _size; //size in pixels

    SDL_Rect* _srcRect; //texture source rect
    SDL_Texture* _texture; //image texture

};
#endif