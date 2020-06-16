#include "Socket.h"
#include "Message.h"
#include "include/FruitInfo.h"
#include <iostream>

int main(int argc, char **argv)
{
    Socket socket (argv[1], argv[2]);

    Message msg;
    msg._type = Message::LOGIN;
    socket.send(msg, socket);

    FruitInfo info;
    info.x = 55;
    Message em(info);
    em._type = Message::FRUIT_EATEN;

    socket.send(em, socket);



    // Message ms;
    // ms._type = Message::LOGOUT;
    // socket.send(ms, socket);

    std::cout << "Messages sent\n";

    return 0;
}