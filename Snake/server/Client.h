#ifndef _H_Client_H_
#define _H_Client_H_

class Socket;
class InputInfo;

class Client
{
public:
    Client(const char * s, const char * p);
    ~Client();

    void SendInput(InputInfo info);

    void SendFruit();


private:
    Socket* _socket = nullptr;

};
#endif