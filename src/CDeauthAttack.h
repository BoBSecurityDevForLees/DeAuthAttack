#pragma once

#include <vector>
#include <pcap.h>
#include <unistd.h>
#include "CRadioHeader.h"
#include "CDeauthentication.h"

enum AttackType
{
    BroadDeauth = 0,
    UnicastDeauth = 1,
    Auth = 2,
};

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