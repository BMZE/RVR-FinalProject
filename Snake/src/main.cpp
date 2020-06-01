#include "Platform.h"
#include <iostream>



int main() 
{
    if(!Platform::Init())
        return 1;

    //game loop
    

    Platform::Release();
    return 0;
}