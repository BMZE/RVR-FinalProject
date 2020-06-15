#include "Client.h"
#include "Socket.h"
#include "Message.h"
#include "InputInfo.h"

Client::Client(const char * s, const char * p)
{
    _socket = new Socket(s, p);
    //_socket->Bind();
}

void Client::SendInput(InputInfo info)
{
    Message msg(info);
    _socket->send(msg, *_socket);
}

void Client::SendFruit()
{

}

Client::~Client()
{
    delete _socket;
    _socket = nullptr;
}