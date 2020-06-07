#include <iostream>
#include "Platform.h"
#include "Renderer.h"
#include "Input.h"
#include "Game.h"

int main() 
{
    std::cout << "Initializing...\n";

    //Initialize SDL 
    if(!Platform::Init())
        return 1;
    if(!Renderer::Init())
        return 1;
    Input::Init();


    Game game; 
    
    //game loop
    while(Platform::Input())
    {
        Input::Tick(); //register input

        game.HandleInput();  //translate input

        game.Update(); //update objects
        
        Renderer::Clear(0); //clears last frame
        game.Render();  //render new frame
        Renderer::Present(); //display the new frame buffer
    }

    //Release SDL
    Input::Release();
    Renderer::Release();
    Platform::Release();
        
    return 0;
}