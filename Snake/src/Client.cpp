#include "Client.h"
#include "../server/Socket.h"
#include "../server/Message.h"
#include "InputInfo.h"
#include "FruitInfo.h"

#pragma region STATIC ATTRIBUTES

Socket* Client::_socket = nullptr;
volatile bool Client::_rcvInput = false;
volatile bool Client::_rcvFruit = false;

#pragma endregion

void Client::Init(const char * s, const char * p)
{
    _socket = new Socket(s, p);
    Login();
    //_socket->Bind();
}

//Login to game server
void Client::Login()
{
    Message msg;
    msg._type = Message::LOGIN;
    _socket->send(msg, *_socket);   
}

//Logout from game server
void Client::Logout()
{
    Message msg;
    msg._type = Message::LOGOUT;
    _socket->send(msg, *_socket);  
}

//If direction has changed, sends new input to server
void Client::SendInput(InputInfo info)
{
    Message msg(info);
    msg._type = Message::INPUT;
    _socket->send(msg, *_socket);
}

void Client::SendFruit(FruitInfo info)
{
    Message msg(info);
    msg._type = Message::FRUIT_EATEN;
    _socket->send(msg, *_socket);
}

void Client::net_thread()
{
    while (true)
    {
        Message msg;
        _socket->recv(msg, _socket);

        if(msg._type == Message::INPUT)
        {
            _rcvInput = true;
        }    
        else if (msg._type == Message::FRUIT_EATEN)
        {
            _rcvFruit = true;
        }
    }
    
}

bool Client::RecvInput()
{
    return _rcvInput;
}

bool Client::RecvFruit()
{
    return _rcvFruit;
}

void Client::Release()
{
    Logout();
    delete _socket;
    _socket = nullptr;
}
