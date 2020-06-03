#ifndef _H_InputListener_H_
#define _H_InputListener_H_

class SDL_Event;

class InputListener 
{
public:

    InputListener();
    ~InputListener();

    void OnEvent(const SDL_Event& event);

    const SDL_Event& GetInput();

private:

    SDL_Event* _event;

};
#endif