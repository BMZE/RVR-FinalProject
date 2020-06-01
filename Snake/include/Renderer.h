#ifndef _H_Renderer_H_
#define _H_Renderer_H_
#include <string>

class SDL_Renderer;
class SDL_Surface;

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

    /**
     * Returns screen width
     */
    static inline int GetScreenWidth(){ return _screenWidth; };

    /**
     * Returns screen height
     */
    static inline int GetScreenHeight(){ return _screenHeight; };

    /**
     * Loads and returns an image texture
     */
    static SDL_Surface* LoadImage(std::string* path);

private:

    static SDL_Renderer* _pRenderer;
    static SDL_Surface* _screenSurface;
    static int _screenWidth;
    static int _screenHeight;
};
#endif