#include "../server/Socket.h"
#include "../server/Message.h"
#include <iostream>

int main(int argc, char **argv)
{
    Socket socket (argv[1], argv[2]);

    Message msg;
    msg._type = Message::LOGIN;

    msg.to_bin();
    msg.from_bin(msg.data());

    socket.send(msg, socket);

    Message ms;
    ms._type = Message::LOGOUT;
    socket.send(ms, socket);

    std::cout << "Messages sent\n";

    return 0;
}