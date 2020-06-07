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
    
};
#endif