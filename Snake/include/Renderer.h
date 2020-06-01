#ifndef _H_Renderer_H_
#define _H_Renderer_H_

class SDL_Renderer;
class SDL_Texture;

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
     * Returns the SDL renderer
     */
    static SDL_Renderer* GetRenderer(); 

    /**
     * Loads and returns an image texture
     */
    static SDL_Texture* LoadImage(const char* path);

private:

    static SDL_Renderer* _pRenderer;
    static int _screenWidth;
    static int _screenHeight;
};
#endif