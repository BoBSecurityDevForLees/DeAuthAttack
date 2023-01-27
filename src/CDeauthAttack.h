#pragma once

#include <vector>
#include <pcap.h>
#include <unistd.h>
#include "CRadioHeader.h"
#include "CDeauthentication.h"

class CDeauthenticationAttack
{
private:
    C80211RadioHeader radioHeader;
    C80211Deauthentication deauthentiocation;
    
    std::vector<char*> packetlist;
    int packetSize = 0;

public:
    CDeauthenticationAttack(int option);
    ~CDeauthenticationAttack();

    bool generatePacket(char* strApMac, char* strStationMac, int option);
    void sendPacket(pcap_t* handle, char* strApMac, char* strStationMac, int option);
};