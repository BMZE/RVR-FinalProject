#include "Platform.h"
#include <iostream>
#include <SDL2/SDL.h>

#pragma region  STATIC ATTRIBUTES

SDL_Window* Platform::pWindow = nullptr;
const int Platform::SCREEN_WIDTH = 400;
const int Platform::SCREEN_HEIGHT =  400;
#pragma endregion

#pragma region PUBLIC METHODS

//Creates SDL window
bool Platform::Init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not be initilized! \nSDL_Error: " << SDL_GetError() << '\n';
        return false;
    }
    else
    {
        pWindow = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    }
    
    if(pWindow == nullptr)
    {
        std::cout << "Window could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
        return false;
    }
 
        
    return true;
}

void Platform::Input()
{

}

void Platform::Release()
{
    SDL_DestroyWindow(pWindow);
    pWindow = nullptr;
}

#pragma endregion