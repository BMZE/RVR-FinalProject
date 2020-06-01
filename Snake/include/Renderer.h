#pragma once

class SDL_Renderer;

class Renderer 
{
public:

    /**
     * Initialises the renderer
     */
    static bool Init();

    /**
     * Clears the window by painting it all with one color
     * @param color Color to paint the window
     */
    static void Clear(int color);

    /**
     * Updates the window to the current display buffer
     */
    static void Present();

    /**
     * Releases SDL resources
     */
    static void Release();

private:

    static SDL_Renderer* _pRenderer;

};