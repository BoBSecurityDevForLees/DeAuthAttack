#pragma once
#pragma pack(1)

#include <iostream>
#include <cstring>
#include "mac.h"

typedef u_char BYTE;

class C80211Deauthentication
{
private:
    uint16_t framecontrol;
    uint16_t duration;
    Mac macDestinationAddress;
    Mac macSourceAddress;
    Mac macBSSID;
    uint sequenceNum = 0;
    uint16_t byteDeauthFixed;
    BYTE byteAuthFixed[6];

public:
    C80211Deauthentication();
    C80211Deauthentication(char* strBSSID);
    C80211Deauthentication(char* strBSSID, char* strDestination);
    ~C80211Deauthentication();

    bool getDeauthenticationPacket(char* packet);
    bool getAuthenticationPacket(char* packet);
    int getDeauthenticationPacketSize();
    int getAuthenticationPacketSize();
};