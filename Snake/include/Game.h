#ifndef _H_Game_H_
#define _H_Game_H_
#include <vector>

class Player;

class Game 
{
public:
    Game();
    ~Game();

    void Update();

    void Render();
    

private: 

    std::vector<Player*> _players;
    const int TILE_PIXEL_SIZE = 20;
    
    std::vector<std::vector<bool>> _tilemap; //game tiles (columns and rows)
    
};
#endif