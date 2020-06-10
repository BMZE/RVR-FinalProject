#ifndef _H_GameObject_H_
#define _H_GameObject_H_

class GameObject 
{
public:
    enum Type {Snake,  Fruit}; //GameObject types

    GameObject() {};
    virtual ~GameObject(){};

    /**
     * Updates GameObject
     */
    virtual void Update() = 0;

    /**
     * Renders GameObject
     */
    virtual void Render() = 0;

    /**
     * @return Type of GameObject (snake/fruit/...)
     */
    virtual Type GetType() = 0;


protected:
    Type _type; //GameObject type
    
};

#endif