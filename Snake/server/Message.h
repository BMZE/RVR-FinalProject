#ifndef _H_Message_H_
#define _H_Message_H_

#include "Serializable.h"
#include <string>
#include "../include/InputInfo.h"
#include "../include/FruitInfo.h"


class Message : public Serializable
{
public:
    Message(){};
    Message(const InputInfo &info);
    ~Message();

    void to_bin();

    int from_bin(char * data);

    enum MessageType { LOGIN, INPUT, FRUIT_EATEN, LOGOUT };

    uint8_t _type;

private:

    static const size_t INPUT_SIZE = sizeof(InputInfo) + sizeof(uint8_t);
    static const size_t FRUIT_SIZE = sizeof(FruitInfo) + sizeof(uint8_t);

    InputInfo _inputInfo;
    FruitInfo _fruitInfo;
};
#endif