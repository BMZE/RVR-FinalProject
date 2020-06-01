#include <iostream>
#include "Platform.h"
#include "Renderer.h"
#include "Game.h"

int main() 
{
    //Initialize SDL 
    if(!Platform::Init())
        return 1;
    if(!Renderer::Init())
        return 1;

    Game game;
    

    //game loop
    while(Platform::Input())
    {
        game.HandleInput();  //register input
        game.Update(); //update objects

        Renderer::Clear(0); //clears last frame
        game.Render();  //render new frame
        Renderer::Present(); //display the new frame buffer
    }

    Renderer::Release();
    Platform::Release();
        
    return 0;
}