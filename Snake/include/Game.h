#ifndef _H_Game_H_
#define _H_Game_H_
#include <vector>

class Player;
class SDL_Texture;

class Game 
{
public:
    Game();
    ~Game();

    void Update();

    void Render();
    
    void HandleInput();

private: 

    std::vector<Player*> _players;
    SDL_Texture* test;
};
#endif