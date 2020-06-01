#include "Platform.h"
#include <iostream>



int main() 
{
    if(!Platform::Init())
        return 1;

    //game loop

    while(Platform::Input())
    {

    }

    Platform::Release();
    return 0;
}