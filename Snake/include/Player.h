#ifndef _H_Player_H_
#define _H_Player_H_

class Player 
{
public:
    Player(int x, int y);
    ~Player();

private:
    int _xPos;
    int _yPos;
    int _height;
    int _width;
};

#endif