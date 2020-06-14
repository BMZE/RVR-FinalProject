#ifndef _H_Server_H_
#define _H_Server_H_

#include <vector>

class Socket;

class Server 
{
public:
    Server(const char * s, const char * p);
    ~Server();

    void ProcessMessages();


private:

    /**
     *  Lista de clientes conectados al servidor de Chat, representados por
     *  su socket
     */
    std::vector<Socket *> _clients;

    /**
     * Socket del servidor
     */
    Socket* _socket = nullptr;

};
#endif