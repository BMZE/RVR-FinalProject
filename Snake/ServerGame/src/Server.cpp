#include "Server.h"
#include <string>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <pthread.h>

#include "Message.h"
#include "Socket.h"
#include "InputInfo.h"
#include "../ServerGame/include/ServerGame.h"

ServerGame* Server::_game  = nullptr;
volatile bool Server::_inputRegistered = false;
InputInfo* Server::_playersInput = nullptr;

Server::Server(const char * s, const char * p)
{
    _socket = new Socket(s, p);
    _socket->Bind();

    _clients.reserve(MAX_PLAYERS);
    // _playersInput.resize(MAX_PLAYERS);
    _playersInput = new InputInfo[MAX_PLAYERS];
}


void Server::ProcessMessages()
{
    std::cout << "Snake server is running\n" << "Waiting for players to join\n";
    int playersReady = 0;
    int inputRecv = 0;

    while(true)
    {
        Socket* client;
        Message msg;
        _socket->recv(msg, client);

        switch(msg._type)
        {
            case Message::LOGIN:
                if(_clients.size() < MAX_PLAYERS)
                {
                    _clients.push_back(client);
                    std::cout << "Player " << _clients.size() << " joined the game\n";

                    if(_clients.size() == MAX_PLAYERS)
                    {
                        for(int i = 0; i < _clients.size(); i++) //notify clients and send player id 
                        {
                            Message ms(Message::INIT); 
                            ms._player = i + '0';
                            _socket->send(ms, *_clients[i]);
                        }
                    }
                }
                else
                {
                    std::cout << "Maximum number of players reached\n";
                }  
            break;

            case Message::READY:
                playersReady++;
                if(playersReady == MAX_PLAYERS) //TODO:change to INIT -> READY -> START
                {
                    CreateGameThread(); //Thread to run game
                    SendToClients(Message(Message::START));
                    std::cout << "Game ready\n";
                }
            break;

            case Message::INPUT:
                inputRecv++;
                _playersInput[(msg._player-'0')] = InputInfo(msg._inputInfo); 
                
                if(inputRecv == MAX_PLAYERS)
                {
                    inputRecv = 0;
                    _inputRegistered = true;
                }
                //std::cout << "Input received\n";
            break;

            case Message::LOGOUT:
                int player = 0;
                for(Socket* sock: _clients)
                {
                    if((*sock == *client))
                    {
                        _clients.erase(_clients.begin() + player);
                        //TODO: REVISE FOR CORRECT PLAYER ID
                        std::cout << "Player " << player + 1 << " exited game" << std::endl;
                        break;
                    }
                    player++;
                }
            break;
        }
    }
}

//Sends a message to all clients connected to the server
void Server::SendToClients(Message msg)
{
    for(Socket* sock: _clients) //TODO: send to game
    {
        _socket->send(msg, *sock);
    }
}

void Server::CreateGameThread()
{
    pthread_t gameThread; //thread
    pthread_attr_t attr;

    _game = new ServerGame(this);
    _game->Init(); //initialize game before

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int res = pthread_create(&gameThread, &attr, RunGame, NULL);

    if(res != 0)
        std::cout << "Error, Thread was not created\n";
}

void* Server::RunGame(void*)
{
    while (true)
    {
        if(_inputRegistered)
        {
            _inputRegistered = false;
            _game->SetInputInfo(_playersInput);
            _game->Update();
        }
    }

}

Server::~Server()
{
    if(_game != nullptr)
    {
        delete _game; _game = nullptr;
    }

    delete _socket;
    _socket = nullptr;

    //Todo: delete players input 
}   