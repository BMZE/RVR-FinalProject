#ifndef _H_Fruit_H_
#define _H_Fruit_H_

#include "GameObject.h" 

class SDL_Texture;
class SDL_Rect;

class Fruit : public GameObject 
{
public:

    Fruit(int x, int y, int size, const char* path);
    ~Fruit();

    void Update();

    void Render();

    inline Type GetType(){ return _type; };

private:

    int _xPos;
    int _yPos;
    int _size;

    SDL_Rect* _srcRect;
    SDL_Texture* _texture; //image texture

};
#endif