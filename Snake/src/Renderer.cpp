#include "Renderer.h"
#include "Platform.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#pragma region  STATIC ATTRIBUTES

SDL_Renderer* Renderer::_pRenderer = nullptr;
int Renderer::_screenWidth = 0;
int Renderer::_screenHeight = 0;

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
        SDL_GetWindowSize(pWindow, &_screenWidth, &_screenHeight);
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

SDL_Texture* Renderer::LoadImage(const char* path)
{
    SDL_Surface* image = SDL_LoadBMP(path);
    
    if(image == nullptr)
        std::cout << "Unable to load image! \nSDL_Error: " << SDL_GetError() << '\n';
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_pRenderer, image);
    SDL_FreeSurface(image); 

    return texture;
}

void Renderer::Release()
{
    SDL_DestroyRenderer(_pRenderer);
    _pRenderer = nullptr;
}

#pragma endregion
