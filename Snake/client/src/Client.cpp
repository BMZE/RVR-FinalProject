#include "Client.h"
#include "../server/Socket.h"
#include "../server/Message.h"
#include "InputInfo.h"
#include "FruitInfo.h"
#include <iostream>
#include <pthread.h>
#include "ClientGame.h"

#pragma region STATIC ATTRIBUTES

Socket* Client::_socket = nullptr;
volatile bool Client::_startGame = false;
volatile bool Client::_initGame = false;
ClientGame* Client::_game = nullptr;
char Client::_id = '0';

#pragma endregion

void Client::Init(const char * s, const char * p, ClientGame* g)
{
    _socket = new Socket(s, p);
    _game = g;

    //Create thread to receive messages from server
    pthread_t recvThread;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int res = pthread_create(&recvThread, &attr, net_thread, NULL);

    if(res != 0)
        std::cout << "Error, Thread was not created\n";

    Login();
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
    Message msg(Message::INPUT, info, _id);
    _socket->send(msg, *_socket);
}

void Client::SendGameReady()
{
    Message msg(Message::READY);
    _socket->send(msg, *_socket);
}

void* Client::net_thread(void*)
{
    while (true)
    {
        Socket* server;
        Message msg;
        _socket->recv(msg, server);

        if (msg._type == Message::FRUIT_EATEN)
        {
           _game->FruitRellocated(&msg._fruitInfo);
        }
        else if(msg._type == Message::NODE)
        {
            _game->UpdatePlayerSnakeHead(msg._node, (msg._player - '0'));
        }
        else if(msg._type == Message::ADD_NODE)
        {
            _game->AddNodeToSnake(msg._node,(msg._player - '0'));
        }
        else if(msg._type == Message::INIT)
        {
            _id = msg._player;
            _initGame = true;
        }
        else if(msg._type == Message::START)
        {
            _startGame = true;
        }
    }
    
}

void Client::Release()
{
    Logout();
    delete _socket;
    _socket = nullptr;
}
