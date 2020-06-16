#ifndef _H_Client_H_
#define _H_Client_H_

class Socket;
class InputInfo;
class FruitInfo;

class Client
{
public:
    static void Init(const char * s, const char * p);

    static void Release();

    static void net_thread();

    /**
     * Login to game server
     */
    static void Login();

    /**
     * Logout from game server
     */
    static void Logout(); 

    /**
     * If direction has changed, sends new input to server
     * @param info InputInfo with frame's input information
     */
    static void SendInput(InputInfo info);

    /**
     * If the other player's direction has changed, 
     * receive new input information from server
     */
    static bool RecvInput(); 

    static void SendFruit(FruitInfo info);

    static bool RecvFruit();

private:
    static Socket* _socket;
    static volatile bool _rcvInput;
    static volatile bool _rcvFruit;

};
#endif