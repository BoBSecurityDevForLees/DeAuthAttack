#include "CDeauthentication.h"

C80211Deauthentication::C80211Deauthentication()
{
    
}

C80211Deauthentication::C80211Deauthentication(char* strBSSID)
{
    this->framecontrol = 0x00c0;
    this->duration = 0;
    this->macDestinationAddress = this->macDestinationAddress.broadcastMac();
    this->macBSSID = Mac(strBSSID);
    this->macSourceAddress = Mac(strBSSID);
    this->byteDeauthFixed = 0x0070;
}
// B=A, D S
C80211Deauthentication::C80211Deauthentication(char* strBSSID, char* strDestination)
{
    this->framecontrol = 0x00c0;
    this->duration = 0;
    this->macDestinationAddress = Mac(strDestination);  // S
    this->macBSSID = Mac(strBSSID);                     // A
    this->macSourceAddress = Mac(strBSSID);             // A
}

C80211Deauthentication::~C80211Deauthentication()
{

}

bool C80211Deauthentication::getDeauthenticationPacket(char* packet)
{
    memcpy(&packet[0], &this->framecontrol, 2);
    memcpy(&packet[2], &this->duration, 2);
    memcpy(&packet[4], &this->macDestinationAddress, 6);
    memcpy(&packet[10], &this->macSourceAddress, 6);
    memcpy(&packet[16], &this->macBSSID, 6);
    uint16_t sequenceFrame = this->sequenceNum << 4;
    memcpy(&packet[22], &sequenceFrame, 2);
    memcpy(&packet[24], &this->byteDeauthFixed, 2);
    
    this->sequenceNum = (this->sequenceNum +1) % 16777216;
    return true;
}

bool C80211Deauthentication::getAuthenticationPacket(char* packet)
{
    // D: A
    // S: S
    // B: A
    this->framecontrol = 0x00b0;
    memcpy(&packet[0], &this->framecontrol, 2);
    memcpy(&packet[2], &this->duration, 2);
    memcpy(&packet[4], &this->macDestinationAddress, 6);
    memcpy(&packet[10], &this->macSourceAddress, 6);
    memcpy(&packet[16], &this->macDestinationAddress, 6);
    uint16_t sequenceFrame = this->sequenceNum << 4;
    memcpy(&packet[22], &sequenceFrame, 2);

    BYTE byteAuthFixed[6] = { 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 };
    memcpy(&packet[24], &byteAuthFixed, 6);

    this->sequenceNum = (this->sequenceNum +1) % 16777216;
    return true;
}

int C80211Deauthentication::getDeauthenticationPacketSize()
{
    return 26;
}

int C80211Deauthentication::getAuthenticationPacketSize()
{
    return 30;
}