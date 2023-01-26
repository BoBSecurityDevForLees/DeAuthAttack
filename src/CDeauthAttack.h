#pragma once

#include "CRadioHeader.h"
#include "CDeauthentication.h"

class CDeauthenticationAttack
{
private:
    C80211RadioHeader radioHeader;
    C80211Deauthentication* deauthentication;

    char* packet;
    int packetSize=0;

public:
    CDeauthenticationAttack(char* strApMac);
    CDeauthenticationAttack(char* strApMac, char* strStationMac);
    ~CDeauthenticationAttack();

    u_char* getDeauthenticationPacket();
    int getDeauthenticationPacketSize();
};