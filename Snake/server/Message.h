#ifndef _H_Message_H_
#define _H_Message_H_

#include <string>
#include "../include/InputInfo.h"
#include "../include/FruitInfo.h"


class Message
{
public:
    Message();
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

    enum MessageType { LOGIN, INPUT, FRUIT_EATEN, LOGOUT };

    uint8_t _type;

private:

    static const size_t INPUT_SIZE = sizeof(InputInfo) + sizeof(uint8_t) + sizeof(char);
    static const size_t FRUIT_SIZE = sizeof(FruitInfo) + sizeof(uint8_t) + (sizeof(char) * 2);

    InputInfo _inputInfo;
    FruitInfo _fruitInfo;

    int32_t _size = 0;

    char *  _data = nullptr;
};
#endif