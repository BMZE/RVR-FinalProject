#ifndef _H_Platform_H_
#define _H_Platform_H_
#include <list>

class SDL_Window;
class InputListener;
union SDL_Event;


class Platform 
{

public:

#pragma region PLATFORM SETUP
    /**
     * Creates the SDL window
     */
    bool static Init();

    /**
     * Registers user input
     * @return true if SDL_Quit
     */
    bool static Input();

    /**
     * Releases the resources used by SDL
     */
    void static Release(); 

#pragma endregion

#pragma region EMITTER METHODS

    /**
     * Add listener to list
     * @param listener to add
     */
    static void AddListener(InputListener* listener);

    /**
     * Removes specific listener from list
     * @param listener to remove
     */
    static void RemoveListener(InputListener* listener);

    /**
     * Sends the new input info to the input listeners
     * @param e SDL_Event with the input info
     */
    static void SendMessage(const SDL_Event& e);

#pragma endregion

    /**
     * Returns sdl window
     */
    inline static SDL_Window* GetWindow() { return _pWindow; };


private:

    //Screen width & height
    static const int SCREEN_WIDTH;
    static const int SCREEN_HEIGHT; 

    static SDL_Window* _pWindow; 

    static std::list<InputListener*> _listeners;
};
#endif