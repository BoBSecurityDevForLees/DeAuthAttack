#include <iostream>
#include <pcap.h>

void usage()
{
    std::cerr << "syntax : deauth-attack <interface> <ap mac> [<station mac> [-auth]]" << std::endl;
    std::cerr << "sample : deauth-attack mon0 00:11:22:33:44:55 66:77:88:99:AA:BB" << std::endl;
}

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        usage();
        return -1;
    }
    


    return 0;
}