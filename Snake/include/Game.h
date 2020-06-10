#ifndef _H_Game_H_
#define _H_Game_H_
#include <vector>

//FORWARD DECLARATIONS
class Player;
class GameObject;

struct Tile //info  in tilemap
{
    bool empty = true; //tile state
    GameObject* go = nullptr; //GameObject in tile if not empty
};

class Game 
{
public:
    Game();
    ~Game();

    /**
     * Updates GameObjects
     */
    void Update();

    /**
     * Renders GameObjects
     */
    void Render();

    /**
     * Relocates fruit once eaten
     */
    void FruitEaten(int x, int y);

    /**
     * @return tile map info
     */
    std::vector<std::vector<Tile>> GetTilemap();

    /**
     * Modifies info in tile map
     */
    void SetTile(int x, int y, Tile tile);

private: 

    void InitTilemap(); //Initializes the tile map

    const int TILE_PIXEL_SIZE = 20; 
    
    std::vector<std::vector<Tile>> _tilemap; //game tiles (columns and rows)
    
    std::vector<GameObject*> _gameObjects; //Active GameObjects
};
#endif