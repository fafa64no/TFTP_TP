#include "gettftp.h"

int main(int argc, char** argv) {
    struct addrinfo hostCfg = getAddrCfg(argc, argv);

    int sock = getSocket();
    char* filename = argv[2];

    readSocket(sock, &hostCfg, filename);

    return EXIT_SUCCESS;
}