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
     * @param x coordinate X of latest fruit position
     * @param y coordinate Y of latest fruit position
     */
    void FruitEaten(int x, int y);

    /**
     * @return tile map info
     */
    std::vector<std::vector<GameObject*>> GetTilemap();

    /**
     * Modifies info in tile mapç
     */
    void SetTile(int x, int y, GameObject* go);

    /**
     * Sets the received input of each player
     * @param info InputInfo of current clients
     */
    void SetInputInfo(InputInfo* info);

    /**
     * Sends message to all clients
     * @param msg message to send
     */
    void SendToClients(Message msg);

    /**
     * @return true if a player has collided
     */
    inline bool PlayerLost(){ return _gameLost; };

    /**
     * Call to make when a snake has collided
     */
    void PlayerCollided();

private: 
    
    void InitTilemap(); //Initializes the tile map

    void InitPlayers(); //Creates depending if Player 1 || Player 2 
    
    std::vector<std::vector<GameObject*>> _tilemap; //info of wich GameObject is or not in each tile
    
    std::vector<GameObject*> _gameObjects; //Active GameObjects

    std::vector<ServerPlayer*> _players; //Active Players

    ServerFruit* _fruit = nullptr;

    Server* _server = nullptr;

    bool _gameLost = false; //true when a player has collided
};
#endif