#include "Platform.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "InputListener.h"

#pragma region  STATIC ATTRIBUTES

SDL_Window* Platform::_pWindow = nullptr;
const int Platform::SCREEN_WIDTH = 800;
const int Platform::SCREEN_HEIGHT = 600;
std::list<InputListener*> Platform::_listeners;

#pragma endregion

#pragma region PLATFORM SETUP

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
        _pWindow = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    }
    
    if(_pWindow == nullptr)
    {
        std::cout << "Window could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
        return false;
    }
 
        
    return true;
}

bool Platform::Input()
{
    SDL_Event e;

    while(SDL_PollEvent(&e))
    {
        //Exits program when pressing ESC or X button
        if(e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT)
        {
            //TODO: SEND QUIT TO SERVER
            SDL_Quit();
            return false;
        }
    }

    return true;
}

void Platform::Release()
{
    SDL_DestroyWindow(_pWindow);
    _pWindow = nullptr;
}

#pragma endregion

#pragma region EMITTER METHODS

    void Platform::AddListener(InputListener* listener)
    {
        _listeners.push_back(listener);
    }

    void Platform::RemoveListener(InputListener* listener)
    {
        _listeners.remove(listener);
    }

    void Platform::SendMessage(const SDL_Event& e)
    {
        for(InputListener* listener : _listeners)
        {  
            listener->OnEvent(e)
        }
    }

#pragma endregion