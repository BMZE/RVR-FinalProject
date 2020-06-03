#include "InputListener.h"
#include <SDL2/SDL_events.h>
#include "Platform.h"

InputListener::InputListener()
{
    Platform::AddListener(this);
}


InputListener::~InputListener()
{

}

void InputListener::OnEvent(const SDL_Event& event)
{
    _event = event;
}

const SDL_Event& InputListener::GetInput()
{
    return _event;
}