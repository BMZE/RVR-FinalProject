#ifndef _H_InputInfo_H_
#define _H_InputInfo_H_
#include <string>

struct InputInfo
{
    bool right = false;
    bool left = false;
    bool forward = false;
    bool back = false;

    std::string toString()
    {
        std::string str = std::to_string(right) + std::to_string(left)
            + std::to_string(forward) + std::to_string(back) + '\0';
        
        return str;
    }

    void fromString(const char* str)
    {
        right = (str[0] - '0');
        left = (str[1] - '0');
        forward = (str[2] - '0');
        back = (str[3] - '0');
    }
};

#endif