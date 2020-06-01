#pragma once

class SDL_Window;

class Platform 
{

public:

    /**
     * Creates the SDL window
     */
    bool static Init();

    void static Input();

    /**
     * Releases the resources used by SDL
     */
    void static Release(); 

private:

    //Screen width & height
    static const int SCREEN_WIDTH;
    static const int SCREEN_HEIGHT; 

    static SDL_Window* pWindow;

};