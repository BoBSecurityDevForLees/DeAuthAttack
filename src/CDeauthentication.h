#pragma once

#include <iostream>
#include <cstring>

class C80211Deauthentication
{
private:
    uint16_t framecontrol;
    uint16_t duration;
    u_char strDestinationAddress[6];
    u_char strSourceAddress[6];
    u_char strBSSID[6];
    uint sequenceNum = 0;
    uint16_t byteFixed;

public:
    C80211Deauthentication(char* strBSSID);
    C80211Deauthentication(char* strBSSID, char* strDestination);
    ~C80211Deauthentication();

    bool getDeauthenticationPacket(char* packet);
    int getDeauthenticationPacketSize();
};