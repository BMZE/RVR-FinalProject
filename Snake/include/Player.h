#ifndef _H_Player_H_
#define _H_Player_H_

class SDL_Texture;
class SDL_Rect;

class Player 
{
public:
    Player(int x, int y, int w, int h, const char* path);
    ~Player();

    void Update();
    void Render();

    SDL_Texture* _texture;

private:

    void Input();

    void Move();

    enum Direction {North, East, South, West , END};

    int _xPos;
    int _yPos;
    int _width;
    int _height;
    
    SDL_Rect* _srcRect;
    Direction _direction;
};

#endif