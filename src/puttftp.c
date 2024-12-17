#include "puttftp.h"

int main(int argc, char** argv) {
    struct addrinfo hostCfg = getAddrCfg(argc, argv);
    struct sockaddr* sockaddr = hostCfg.ai_addr;

    int sock = getSocket();
    
    char* filename = argv[2];

    while(1);

    return EXIT_SUCCESS;
}