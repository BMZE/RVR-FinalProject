#include "Input.h"
#include "InputListener.h"
#include "InputInfo.h"
#include <SDL2/SDL_events.h>
#include <iostream>
#include <list>

#pragma region STATIC ATTRIBUTES

InputListener Input::_inputListener; 
InputInfo Input::_inputInfo;

#pragma endregion

#pragma region SINGLETON

void Input::Init()
{
    _inputListener.Init();
}

void Input::Tick()
{
    std::list<SDL_Event>eventList = _inputListener.GetInput();
    
    for(auto event : eventList)
    {
        if(event.type == SDL_KEYDOWN)
        {
             IsKeyDown(event);   
        }
        else if(event.type == SDL_KEYUP)
            IsKeyUp(event);
    }   
}

InputInfo Input::GetInputInfo()
{
    return _inputInfo;
}

void Input::Release()
{

}

#pragma endregion

#pragma region KEY MANAGEMENT

void Input::IsKeyDown(const SDL_Event & event)
{
    
    switch (event.key.keysym.sym)
    {
    //button keys
    case SDLK_a:
        _inputInfo.left = true;    
        break;
    case SDLK_d:
        _inputInfo.right = true;
        break;
    case SDLK_w:
        _inputInfo.forward = true;
        break;
    case SDLK_s:
        _inputInfo.back = true;
        break;

    //arrow keys
     case SDLK_LEFT:
        _inputInfo.left = true;
        break;
    case SDLK_RIGHT:
         _inputInfo.right = true;
        break;
    case SDLK_UP:
        _inputInfo.forward = true;
        break;
    case SDLK_DOWN:
        _inputInfo.back = true;
    default:
        break;
    }
}

void Input::IsKeyUp(const SDL_Event & event)
{
    switch (event.key.keysym.sym)
    {
    //button keys
     case SDLK_a:
        _inputInfo.left = false;
        break;
    case SDLK_d /*|| SDLK_RIGHT*/:
        _inputInfo.right = false;
        break;
    case SDLK_w:
        _inputInfo.forward = false;
        break;
    case SDLK_s:
        _inputInfo.back = false;
        break;

    //arrow keys
    case SDLK_LEFT:
        _inputInfo.left = false;
        break;
    case  SDLK_RIGHT:
        _inputInfo.right = false;
        break;
    case SDLK_UP:
        _inputInfo.forward = false;
        break;
    case SDLK_DOWN:
        _inputInfo.back = false;
        break;
    default:
        break;
    }
}

#pragma endregion
