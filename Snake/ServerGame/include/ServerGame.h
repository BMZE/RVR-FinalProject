#ifndef _H_ServerGame_H_
#define _H_ServerGame_H_
#include <vector>

//FORWARD DECLARATIONS
class Server;
class GameObject;
class ServerPlayer;
class ServerFruit;
struct FruitInfo; 
struct InputInfo;
class Message;

struct Tile //info  in tilemap
{
    bool empty = true; //tile state
    GameObject* go = nullptr; //GameObject in tile if not empty
};

class ServerGame 
{
public:
    ServerGame(Server* server);
    ~ServerGame();

    /**
     * Initializes game (tilemap, players, fruit)
     */
    void Init();

    /**
     * Updates GameObjects
     */
    void Update();

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

    /**
     * Sets the received input of each player
     * @param info InputInfo of current clients
     */
    void SetInputInfo(InputInfo* info);

    void SendToClients(Message msg);

private: 

    int test = 0;
    
    void InitTilemap(); //Initializes the tile map

    void InitPlayers(); //Creates depending if Player 1 || Player 2 
    
    std::vector<std::vector<Tile>> _tilemap; //game tiles (columns and rows)
    
    std::vector<GameObject*> _gameObjects; //Active GameObjects

    std::vector<ServerPlayer*> _players;

    ServerFruit* _fruit = nullptr;

    Server* _server = nullptr;

    
};
#endif