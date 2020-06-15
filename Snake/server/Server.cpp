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

    int count = 0;

    while(true)
    {
        Socket* client;
        Message msg;
        _socket->recv(msg, client);

        int t = msg._type;
        std::cout << "TYPE: " << t << '\n'; 
        switch(msg._type)
        {
            case Message::LOGIN:
                count++;
                _clients.push_back(client);
                std::cout << "Player " << count << " joined the game\n";
            break;

            case Message::INPUT:
                for(Socket* sock: _clients)
                {
                     if(!(*sock == *client))
                        _socket->send(msg, *sock);
                }
            break;

            case Message::FRUIT_EATEN:
                for(Socket* sock: _clients)
                {
                     if(!(*sock == *client))
                        _socket->send(msg, *sock);
                }
            break;

            case Message::LOGOUT:
                int player = 0;
                for(Socket* sock: _clients)
                {
                    if((*sock == *client))
                    {
                        _clients.erase(_clients.begin() + player);
                        std::cout << "Player " << count << " exited game" << std::endl;
                        count--;
                        break;
                    }
                    player++;
                }
                std::cout << "Logout\n";
            break;
        }
    }
}

Server::~Server()
{
    delete _socket;
    _socket = nullptr;
}