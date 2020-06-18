#ifndef _H_ClientGame_H_
#define _H_ClientGame_H_
#include <vector>
#include "InputInfo.h"

//FORWARD DECLARATIONS
class GameObject;
class ClientPlayer;
class ClientFruit;
struct FruitInfo; 
//struct InputInfo;

struct Tile //info  in tilemap
{
    bool empty = true; //tile state
    GameObject* go = nullptr; //GameObject in tile if not empty
};

class ClientGame 
{
public:
    ClientGame();
    ~ClientGame();

    /**
     * Initializes game (tilemap, players, fruit)
     */
    void Init();

    /**
     * Updates GameObjects
     */
    void Update();

    /**
     * Renders GameObjects
     */
    void Render();

    /**
     * Relocates fruit when the other player has eaten the fruit
     */ 
    void FruitRellocated(FruitInfo* info);

    /**
     * Relocates fruit once eaten
     */
    void FruitEaten(int x, int y);

    /**
     * @return tile map info
     */
    std::vector<std::vector<Tile>> GetTilemap();

    /**
     * Modifies info in tile mapç
     */
    void SetTile(int x, int y, Tile tile);

    void SetInputInfo(InputInfo* info);

private: 

    void InitTilemap(); //Initializes the tile map

    void InitPlayers(); //Creates depending if Player 1 || Player 2

    const int TILE_PIXEL_SIZE = 20; 
    
    std::vector<std::vector<Tile>> _tilemap; //game tiles (columns and rows)
    
    std::vector<GameObject*> _gameObjects; //Active GameObjects

    ClientFruit* _fruit = nullptr;
    ClientPlayer* _otherPlayer = nullptr;
};
#endif