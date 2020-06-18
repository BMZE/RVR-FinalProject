#include "Socket.h"
#include "Message.h"
#include "InputInfo.h"
#include <iostream>

int main(int argc, char **argv)
{
    Socket socket (argv[1], argv[2]);

    Message msg;
    msg._type = Message::LOGIN;
    socket.send(msg, socket);

    InputInfo info;
    info.right = true;
    Message em(info);
    em._type = Message::INPUT;

    socket.send(em, socket);

    // Message ms;
    // ms._type = Message::LOGOUT;
    // socket.send(ms, socket);

    std::cout << "Messages sent\n";

    return 0;
}