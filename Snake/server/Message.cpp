#include "Message.h"
#include <string.h>
#include <iostream>

Message::Message(){}

Message::Message(const InputInfo &info) : _inputInfo(info){}

Message::Message(const FruitInfo &info) : _fruitInfo(info){}


void Message::to_bin()
{
    int t = _type;
    std::cout << "Type: " << t << '\n';

    if(_type == INPUT) //package input info
    {
        alloc_data(INPUT_SIZE);
        char* tmp = _data; 

        memcpy((void*)tmp, (void*)&_type, sizeof(uint8_t));
        _data += sizeof(uint8_t);

        memcpy((void*)tmp, _inputInfo.toString().c_str(), sizeof(char) * (sizeof(InputInfo) + 1)); 
    }
    else if(_type == FRUIT_EATEN) //package fruit info
    {
        alloc_data(FRUIT_SIZE);
        char* tmp = _data;

        memcpy((void*)tmp, (void*)&_type, sizeof(uint8_t));
        tmp += sizeof(uint8_t);

        memcpy((void*)tmp, _fruitInfo.toString().c_str(), sizeof(char) * (sizeof(FruitInfo) + 2)); 
    }
    else //LOGIN OR LOGOUT
    {
        alloc_data(sizeof(uint8_t));
        memcpy((void*)_data, (void*)&_type, sizeof(uint8_t));
    }
    
}

int Message::from_bin(char * data)
{   
    //if type = LOGIN | LOGOUT only _type is read
    char* tmp = data;
    memcpy(&_type, tmp, sizeof(uint8_t)); //read type of message from data
    tmp += sizeof(uint8_t); 

    int t = _type;
    
    std::cout << "Deserialize: " << t << '\n';
    
    if(_type == INPUT) //save inputinfo
    {
        char* str = new char[sizeof(char) * (sizeof(InputInfo) + 1)];
        memcpy(&str[0], tmp, sizeof(char) * (sizeof(InputInfo) + 1));

        _inputInfo.fromString(str);
        delete[] str;
    }
    else if(_type == FRUIT_EATEN) //save fruit info
    {
        char* str = new char[sizeof(char) * (sizeof(FruitInfo) + 2)];
        memcpy(&str[0], tmp, sizeof(char) * (sizeof(FruitInfo) + 2));
        _fruitInfo.fromString(str);
        delete[] str; 
    }

    return 0;
}

Message::~Message()
{
    // if(_data != nullptr)
    // {
    //     delete[] _data;
    //     _data = nullptr;
    // }
}