#include "Renderer.h"
#include "Platform.h"
#include <SDL2/SDL.h>
#include <iostream>

#pragma region  STATIC ATTRIBUTES

SDL_Renderer* Renderer::_pRenderer = nullptr;

#pragma endregion

#pragma region PUBLIC METHODS

bool  Renderer::Init()
{
    SDL_Window* pWindow = Platform::GetWindow();
    _pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

    if(_pRenderer == nullptr)
    {
        std::cout << "Renderer could not be created! \nSDL_Error: " << SDL_GetError() << '\n';
        return false;
    }
    else
    {
        SDL_SetRenderDrawColor(_pRenderer, 0, 0, 0, 255); //Background color = black
        return true;
    }
}

void Renderer::Present()
{
    SDL_RenderPresent(_pRenderer);
}

void Renderer::Clear(int color)
{
    SDL_SetRenderDrawColor(_pRenderer, 
    (color >> 8 * 3) & 0xFF, (color >> 8* 2) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);

    SDL_RenderClear(_pRenderer);
}

void Renderer::Release()
{
    SDL_DestroyRenderer(_pRenderer);
    _pRenderer = nullptr;
}

#pragma endregion
