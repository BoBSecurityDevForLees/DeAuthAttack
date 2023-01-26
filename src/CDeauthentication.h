#pragma once

#include <iostream>
#include <cstring>

typedef u_char BYTE;

class C80211Deauthentication
{
private:
    uint16_t framecontrol;
    uint16_t duration;
    BYTE byteDestinationAddress[6];
    BYTE byteSourceAddress[6];
    BYTE byteBSSID[6];
    uint sequenceNum = 0;
    uint16_t byteFixed;

public:
    C80211Deauthentication(char* byteBSSID);
    C80211Deauthentication(char* byteBSSID, char* byteDestination);
    ~C80211Deauthentication();

    bool getDeauthenticationPacket(char* packet);
    int getDeauthenticationPacketSize();
};