#include <SDL2/SDL.h>
#include <iostream>

int main() 
{
    SDL_Init(SDL_INIT_EVERYTHING);
    std::cout << "Hello world!\n";

    SDL_Quit();

    return 0;
}