#include "CDeauthentication.h"

C80211Deauthentication::C80211Deauthentication(char* byteBSSID)
{
    this->framecontrol = 0x00c0;
    this->duration = 0;
    BYTE byteBroadCast[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
    memcpy(&this->byteDestinationAddress, byteBroadCast, 6);
    memcpy(&this->byteSourceAddress, byteBSSID, 6);
    memcpy(&this->byteBSSID, byteBSSID, 6);
    this->byteFixed = 0x0070;
}

C80211Deauthentication::C80211Deauthentication(char* byteBSSID, char* byteDestination)
{
    this->framecontrol = 0x00c0;
    this->duration = 0;
    memcpy(&this->byteDestinationAddress, byteDestination, 6);
    memcpy(&this->byteSourceAddress, byteBSSID, 6);
    memcpy(&this->byteBSSID, byteBSSID, 6);
}

C80211Deauthentication::~C80211Deauthentication()
{

}

bool C80211Deauthentication::getDeauthenticationPacket(char* packet)
{
    memcpy(&packet[0], &this->framecontrol, 2);
    memcpy(&packet[2], &this->duration, 2);
    memcpy(&packet[4], &this->byteDestinationAddress, 6);
    memcpy(&packet[10], &this->byteSourceAddress, 6);
    memcpy(&packet[16], &this->byteBSSID, 6);
    uint16_t sequenceFrame = this->sequenceNum << 4;
    memcpy(&packet[22], &sequenceFrame, 2);
    memcpy(&packet[24], &this->byteFixed, 2);
    this->sequenceNum = (this->sequenceNum +1) % 16777216;
    return true;
}

int C80211Deauthentication::getDeauthenticationPacketSize()
{
    return 26;
}