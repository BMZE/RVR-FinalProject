#ifndef _H_FruitInfo_H_
#define _H_FruitInfo_H_

#include <string>

struct FruitInfo
{
    int x = 0; //fruit position in tilemap
    int y = 0;

    //converts data separated by '\0' to string
    std::string toString()
    {
        std::string str = std::to_string(x);
        str += '\0';
        str += std::to_string(y);
        str += '\0';
        return str;
    }

    //reconstructs data from string, or const char * due to simplicity
    void fromString(const char* str)
    {
        int i = 0; std::string aux = "";

        while(str[i] != '\0') { aux += str[i]; i++; };
        
        x = std::stoi(aux); 
        
        i++; aux = ""; //discard '\0' and old aux data

        while(str[i] != '\0') { aux += str[i]; i++; };

        y = std::stoi(aux);
    }
};
#endif
