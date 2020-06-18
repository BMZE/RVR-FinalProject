#ifndef _H_Input_H_
#define _H_Input_H_

class InputListener;
class InputInfo;
union SDL_Event;

class Input 
{
public:

    /**
     * Initializes
     */
    static void Init();

    /**
     * 
     */
    static void Tick();

    /**
     * Releases input resources
     */
    static void Release();

    /**
     * Returns the frame's input filtered information
     */ 
    static InputInfo GetInputInfo();

private:

    static void IsKeyDown(const SDL_Event & event);

    static void IsKeyUp(const SDL_Event & event);

    static InputListener _inputListener;
    static InputInfo _inputInfo;
};
#endif
