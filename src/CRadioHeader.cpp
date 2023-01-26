#include "CRadioHeader.h"

// flooding Initializer
C80211RadioHeader::C80211RadioHeader()
{
    // All member Zero
    this->it_version = 0x00;
    this->it_pad = 0x00;
    this->it_len = 11;

    u_char present[4] = { 0x00, 0x80, 0x02, 0x00 };
    memcpy(&this->it_present, present, 4);

    this->it_flag = 0x0000;
    this->it_data_retries = 0;
}

C80211RadioHeader::~C80211RadioHeader()
{

}

bool C80211RadioHeader::getDeAuthPacket(char* packet)
{
    packet[0] = this->it_version;
    packet[1] = this->it_pad;
    memcpy(&packet[2], &this->it_len, 2);
    memcpy(&packet[4], &this->it_present, 4);
    memcpy(&packet[8], &this->it_flag, 2);
    packet[10] = this->it_data_retries;
    return true;
}

int C80211RadioHeader::getDeAuthPacketSize()
{
    return this->it_len;
}