#ifndef _H_Node_H_
#define _H_Node_H_
#include <string>

class Node
{
public:
    Node(int xP, int yP) :x(xP), y(yP){};
    Node(){};
    ~Node(){};

    int x; //position
    int y;

    Node* father = nullptr;
    Node* next = nullptr; 

    enum Direction {North, East, South, West}; //snake direction


    Direction currentDirection = Direction::North;
    Direction lastDirecion = Direction::North;

    //update pos from before method
    void UpdatePosition()
    {
        x = father->x, 
        y = father->y;
    };

    //update current direction from father node
    void UpdateDirections()
    {
        lastDirecion = currentDirection;
        currentDirection = father->lastDirecion;   
    }

    std::string toString()
    {
        std::string str = std::to_string(x) + '\0' + std::to_string(y) + '\0'
            + std::to_string(lastDirecion) + std::to_string(currentDirection) + '\0';
        
        return str;
    }

    void fromString(const char* str)
    {
        int i = 0; std::string aux = "";

        while(str[i] != '\0') { aux += str[i]; i++; };
        
        x = std::stoi(aux); 
        
        i++; aux = ""; //discard '\0' and old aux data

        while(str[i] != '\0') { aux += str[i]; i++; };

        y = std::stoi(aux);

        i++; lastDirecion = (Node::Direction)(str[i] - '0');
        i++; currentDirection = (Node::Direction)(str[i] - '0');
    }
};
#endif