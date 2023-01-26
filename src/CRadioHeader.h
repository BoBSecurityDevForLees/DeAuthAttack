#pragma once

#include <iostream>
#include <cstring>

class C80211RadioHeader
{
private:
    uint8_t it_version;
    uint8_t it_pad;
    uint16_t it_len;
    uint32_t it_present;
    uint16_t it_flag;
    uint8_t it_data_retries;
    

public:
    C80211RadioHeader();                            
    ~C80211RadioHeader();

    bool getDeAuthPacket(char* packet);
    int getDeAuthPacketSize();
};