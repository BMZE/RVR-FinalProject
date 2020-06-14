#include "Message.h"
#include <string.h>
#include <iostream>

Message::Message(const InputInfo &info) : _inputInfo(info)
{
}

Message::Message(const FruitInfo &info) : _fruitInfo(info)
{
}


void Message::to_bin()
{
    std::cout << "serialize: " << _type << '\n';

    if(_type == INPUT) //package input info
    {
        _data = new char[INPUT_SIZE];
        memcpy((void*)_data, (void*)&_type, sizeof(uint8_t));
        _data += sizeof(uint8_t);
        memcpy((void*)_data, &_inputInfo, sizeof(InputInfo)); 
    }
    else if(_type == FRUIT_EATEN) //package fruit info
    {
        _data = new char[FRUIT_SIZE];
        memcpy((void*)_data, (void*)&_type, sizeof(uint8_t));
        _data += sizeof(uint8_t);
        memcpy((void*)_data, &_fruitInfo, sizeof(FruitInfo)); 
    }
    else //LOGIN OR LOGOUT
    {
        _data = new char[sizeof(uint8_t)];
        memcpy((void*)_data, (void*)&_type, sizeof(uint8_t));
    }
    
}

int Message::from_bin(char * data)
{   
    //if type = LOGIN | LOGOUT only _type is read
    memcpy(&_type, data, sizeof(uint8_t)); //read type of message from data
    data += sizeof(uint8_t); 

    std::cout << "Deserialize: " << _type << '\n';
    
    if(_type == INPUT) //save inputinfo
    {
        memcpy(&_inputInfo, data, sizeof(InputInfo));
    }
    else if(_type == FRUIT_EATEN) //save fruit info
    {
        memcpy((void*)_data, &_fruitInfo, sizeof(FruitInfo)); 
    }

    return 0;
}

Message::~Message()
{

}