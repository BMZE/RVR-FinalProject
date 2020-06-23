#ifndef _H_Client_H_
#define _H_Client_H_

class Socket;
class InputInfo;
class FruitInfo;
class ClientGame;

class Client
{
public:
    static void Init(const char * s, const char * p, ClientGame* g);

    static void Release();

    static void* net_thread(void*);

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
     * Notifies server that the client's game has been initialized
     * and is ready to start
     */
    static void SendGameReady();

    static inline bool StartGame(){ return _startGame; };

    static inline bool InitGame(){ return _initGame; };

    static inline char GetID() { return _id; };

private:
    static Socket* _socket;
    static volatile bool _startGame;
    static volatile bool _initGame; 

    static ClientGame* _game;
    static char _id;
};
#endif