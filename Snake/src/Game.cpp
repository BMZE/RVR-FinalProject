#include "Game.h"
#include "Player.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Renderer.h"

Game::Game()
{
    _players.resize(1);
    _players.push_back(new Player(50, 50));
    test = Renderer::LoadImage("bin/Assets/Red.bmp");
}

void Game::Update()
{

}

void Game::Render()
{
    SDL_RenderCopy(Renderer::GetRenderer(), test, NULL, NULL);
}

void Game::HandleInput()
{
    
}

Game::~Game()
{
    delete test;
    test = nullptr;
}