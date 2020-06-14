#include "Message.h"
#include <string.h>

Message::Message(const InputInfo &info) : _inputInfo(info)
{
    // Let's send a packet to the server.
    // char *data = new char[sizeof(PlayerProfile_Struct)];
    // memcpy((void*)data, (void*)&myPlayerProfile, sizeof(PlayerProfile_Struct));
    // Packet outgoingPacket(PLAYER_PROFILE, data, sizeof(PlayerProfile_Struct));  
    // networkManager.synchronousSend(outgoingPacket);
    // delete []data;

}

void Message::to_bin()
{
    _data = new char[sizeof(InputInfo)];
    memcpy((void*)_data, (void*)&_inputInfo, sizeof(InputInfo));
}

int Message::from_bin(char * data)
{

}

Message::~Message()
{

}