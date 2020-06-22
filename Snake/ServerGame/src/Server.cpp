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
InputInfo* Server::_playerOneInput = nullptr;


Server::Server(const char * s, const char * p)
{
    _socket = new Socket(s, p);
    _socket->Bind();
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
                // if(_clients.size() < MAX_PLAYERS)
                // {
                    _clients.push_back(client);
                    std::cout << "Player " << _clients.size() << " joined the game\n";
                    
                    //TODO:change to INIT -> READY -> START
                        
                        /**
                         * Send init message with player id to clients
                         * Create thread for game to run on
                         * once server and all clients ready, START game
                         */
                        // for(int i = 0; i < _clients.size(); i++)
                        // {
                        //     ms._player = (i + 1) + '0';
                        //     _socket->send(ms, *_clients[i]);
                        // }
                // }
                // else
                // {
                //     std::cout << "Maximum number of players reached\n";
                // }  
            break;

            case Message::READY:
                playersReady++;
                if(playersReady == MAX_PLAYERS) //TODO:change to INIT -> READY -> START
                {
                    CreateGameThread();
                    SendToClients(Message (Message::START));
                    std::cout << "Game ready\n";
                }
            break;

            case Message::INPUT:
                //TODO: set depending on player id 
                inputRecv++;
                if(inputRecv == MAX_PLAYERS)
                {
                    _playerOneInput = new InputInfo(msg._inputInfo);
                    inputRecv = 0;
                    _inputRegistered = true;
                }
                //std::cout << "Input received\n";
            break;

            case Message::FRUIT_EATEN:
                for(Socket* sock: _clients) //TODO: send to game
                {
                    _socket->send(msg, *sock);
                }
                //std::cout << "Fruit received\n";
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
        //TODO: WAIT FOR PLAYER INPUT THEN UPDATE
        if(_inputRegistered)
        {
            _inputRegistered = false;
            _game->SetInputInfo(_playerOneInput);
            _game->Update();
            //send new game state to players
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

    delete _playerOneInput;
    _playerOneInput = nullptr;
}   