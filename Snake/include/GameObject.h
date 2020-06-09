#ifndef _H_GameObject_H_
#define _H_GameObject_H_
#include "Game.h"

class GameObject 
{
public:
    enum Type {Snake,  Fruit};

    GameObject() {};
    ~GameObject(){};

    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual Type GetType() = 0;


protected:
    Type _type;

    
};

#endif