#ifndef _H_Fruit_H_
#define _H_Fruit_H_

#include "GameObject.h" 

class Fruit : public GameObject 
{
public:

    Fruit(Type t);
    ~Fruit();

    void Update();

    void Render();

    inline Type GetType(){ return _type; };

private:

};
#endif