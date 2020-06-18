#include "InputListener.h"
#include "Platform.h"
#include <SDL2/SDL_events.h>
#include <iostream>

InputListener::InputListener()
{
   
}


void InputListener::Init()
{
    Platform::AddListener(this);
}


InputListener::~InputListener()
{
    Platform::RemoveListener(this);
}

void InputListener::OnEvent(const SDL_Event& event)
{
        _events.push_back(event);
}

std::list<SDL_Event> InputListener::GetInput()
{
    std::list<SDL_Event> auxList(_events);
	_events.clear();

	return auxList;
}