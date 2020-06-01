#ifndef _H_Player_H_
#define _H_Player_H_

class SDL_Texture;
class Player 
{
public:
    Player(int x, int y, const char* path);
    ~Player();

    void Render();
    SDL_Texture* _texture;

private:
    int _xPos;
    int _yPos;
    int _height;
    int _width;

    
};

#endif