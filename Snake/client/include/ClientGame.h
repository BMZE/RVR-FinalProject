#ifndef _H_ClientGame_H_
#define _H_ClientGame_H_
#include <vector>

//FORWARD DECLARATIONS
class GameObject;
class ClientPlayer;
class ClientFruit;
struct FruitInfo; 
class Node;

class ClientGame 
{
public:
    ClientGame();
    ~ClientGame();

    /**
     * Initializes GameObjects
     */
    void Init();

    /**
     * Renders GameObjects
     */
    void Render();

    /**
     * Relocates fruit when fruit has changed position
     * @param info struct position for fruit
     */ 
    void FruitRellocated(FruitInfo* info);
    
    /**
     * Updates specific snake
     * @param node snake head 
     * @param player specific snake to update
     */
    void UpdatePlayerSnakeHead(Node* node, int player);

    /**
     * Adds node to specific snake
     * @param node new node to add to snake
     * @param player specific snake to add node to
     */
    void AddNodeToSnake(Node* node, int player);

private: 

    void InitPlayers(); //Creates players depending if Player 1 || Player 2

    const int TILE_PIXEL_SIZE = 20; //GameObjects' render size
        
    std::vector<GameObject*> _gameObjects; //Active GameObjects

    std::vector<ClientPlayer*> _players; //Active players

    ClientFruit* _fruit = nullptr; 
};
#endif