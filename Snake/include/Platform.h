#ifndef _H_Platform_H_
#define _H_Platform_H_

class SDL_Window;

class Platform 
{

public:

    /**
     * Creates the SDL window
     */
    bool static Init();

    /**
     * Registers user input
     */
    bool static Input();

    /**
     * Releases the resources used by SDL
     */
    void static Release(); 

    /**
     * Returns sdl window
     */
    inline static SDL_Window* GetWindow() { return _pWindow; };

private:

    //Screen width & height
    static const int SCREEN_WIDTH;
    static const int SCREEN_HEIGHT; 

    static SDL_Window* _pWindow;

};
#endif