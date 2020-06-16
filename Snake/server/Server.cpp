#include "Server.h"
#include <string>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include "Message.h"
#include "Socket.h"

Server::Server(const char * s, const char * p)
{
    _socket = new Socket(s, p);
    _socket->Bind();
}


void Server::ProcessMessages()
{
    std::cout << "Snake server is running\n" << "Waiting for players to join\n";

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
                        Message ms; ms._type  = Message::START;
                        for(int i = 0; i < _clients.size(); i++)
                        {
                            ms._player = (i + 1) + '0';
                            _socket->send(ms, *_clients[i]);
                        }
                    }
                }
                else
                {
                    std::cout << "Maximum number of players reached\n";
                }  
            break;

            case Message::INPUT:
                for(Socket* sock: _clients)
                {
                     if(!(*sock == *client))
                        _socket->send(msg, *sock);
                }
                //std::cout << "Input received\n";
            break;

            case Message::FRUIT_EATEN:
                for(Socket* sock: _clients)
                {
                     if(!(*sock == *client))
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

Server::~Server()
{
    delete _socket;
    _socket = nullptr;
}