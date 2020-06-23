#ifndef _H_Fruit_H_
#define _H_Fruit_H_

#include "GameObject.h" 

//FORWARD DECLARATIONS
class ServerGame;
#include "FruitInfo.h"//class FruitInfo;

class ServerFruit : public GameObject 
{
public:

    ServerFruit(int x, int y);
    ~ServerFruit();

    /**
     * Updates GameObject
     */
    void Update();

    void Render(); //not used in server

    /**
     * @return Type of GameObject (snake/fruit/...)
     */
    inline Type GetType(){ return _type; };

    /**
     * When fruit is eaten, fruit changes position
     * @return new fruit position 
     */
    FruitInfo Rellocate(ServerGame* g);

    /**
     * Returns fruit position
     */
    FruitInfo GetPosition();

    void SetNewPosition(int x, int y, ServerGame* g);
    
private:
    FruitInfo _position;
};
#endif