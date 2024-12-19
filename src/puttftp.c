#include "puttftp.h"

int main(int argc, char** argv) {
    struct addrinfo hostCfg = getAddrCfg(argc, argv);
    struct sockaddr* sockaddr = hostCfg.ai_addr;
    //sockaddr->

    int sock = getSocket();
    
    char* filename = argv[2];

    return EXIT_SUCCESS;
}