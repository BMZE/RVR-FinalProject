#ifndef _H_Message_H_
#define _H_Message_H_

#include "Serializable.h"
#include <string>
#include "InputInfo.h"


class Message : public Serializable
{
public:
    Message(){};
    Message(const InputInfo &info);
    ~Message();

    void to_bin();

    int from_bin(char * data);

    enum MessageType { LOGIN, INPUT, LOGOUT };

    inline uint8_t Type() { return _type; };

private:

    static const size_t MESSAGE_SIZE = sizeof(char) * 88 + sizeof(uint8_t);

    uint8_t _type;
    InputInfo _inputInfo;
};
#endif