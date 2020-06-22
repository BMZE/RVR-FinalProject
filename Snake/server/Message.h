#ifndef _H_Message_H_
#define _H_Message_H_

#include <string>
#include "InputInfo.h"
#include "FruitInfo.h"

class Node;

class Message
{
public:
    Message();
    Message(const uint8_t type);
    Message(const uint8_t type, const InputInfo &info);
    Message(const uint8_t type, const FruitInfo &info);
    Message(const uint8_t type, Node* node);


    Message(const InputInfo &info);
    Message(const FruitInfo &info);
    ~Message();

    void to_bin();

    int from_bin(char * data);

    /**
     *  Devuelve un puntero al buffer interno con la representación del objeto.
     *  Debe inicializarse previamente via Serializable::to_bin()
     *    @return objeto serializado
     */
    inline char * data() { return _data; }

    /**
     *  @return tamaño del objeto serializado
     */
    inline int32_t size() { return _size; };

    enum MessageType { LOGIN, INIT, READY, START, INPUT, NODE, ADD_NODE, UPDATE_PLAYER_POSITION,
        FRUIT_EATEN, LOGOUT };

    uint8_t _type;

    char _player;

    InputInfo _inputInfo;
    FruitInfo _fruitInfo;
    Node* _node;

private:

    static const size_t INPUT_SIZE = sizeof(InputInfo) + sizeof(uint8_t) + sizeof(char);
    static const size_t FRUIT_SIZE = sizeof(FruitInfo) + sizeof(uint8_t) + (sizeof(char) * 2);

    int32_t _size = 0;

    char *  _data = nullptr;
};
#endif