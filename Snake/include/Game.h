#ifndef _H_Game_H_
#define _H_Game_H_
#include <vector>

class Player;
class GameObject;

struct Tile
{
    bool empty = true;
    GameObject* go = nullptr;
};

class Game 
{
public:
    Game();
    ~Game();

    void Update();

    void Render();

    std::vector<std::vector<Tile>> GetTilemap();
    void SetTile(int x, int y, Tile tile);

private: 

    const int TILE_PIXEL_SIZE = 20;
    
    std::vector<std::vector<Tile>> _tilemap; //game tiles (columns and rows)
    std::vector<GameObject*> _gameObjects;
};
#endif