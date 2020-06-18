#include <iostream>
#include "Platform.h"
#include "Renderer.h"
#include "Input.h"
#include "ClientGame.h"
#include <time.h>
#include <SDL2/SDL.h>
#include "Client.h"


int main() 
{
    std::cout << "Initializing...\n";

    //Initialize SDL 
    if(!Platform::Init())
        return 1;
    if(!Renderer::Init())
        return 1;
    Input::Init();

    srand(time(0)); //random seed
    clock_t currentTime = 0;
	double lastFrameTime = 0;
	double elapsedTime = 0;

    float rate = 60.0f; //FPS
	double maxPeriod = 1.0 / rate;

    ClientGame game; 
    Client::Init("127.0.0.1", "7777", &game);

    game.Init(); //game is ready 

    std::cout << "Waiting for other players\n";

    Client::SendGameReady();

    while(!Client::GameStart()); //wait until server is ready


    //game loop
    while(Platform::Input())
    {
        currentTime = clock();
		elapsedTime = (currentTime - lastFrameTime) / 1000;

        //Input
        Input::Tick(); //register input

        //Update
        if (elapsedTime > maxPeriod)
		{
            game.Update(); //update objects
            lastFrameTime = currentTime;
        }

        //Render
        Renderer::Clear(0); //clears last frame
        game.Render();  //render new frame
        Renderer::Present(); //display the new frame buffer  
        SDL_Delay(200);      
    }

    //Release client resources
    Client::Release();

    //Release SDL
    Input::Release();
    Renderer::Release();
    Platform::Release();
        
    return 0;
}