#include "gettftp.h"

int main(int argc, char** argv) {
    struct addrinfo hostCfg = getAddrCfg(argc, argv);
    ssize_t socklen = hostCfg.ai_addrlen;
    struct sockaddr_in* dest_sock = getSockaddr(hostCfg);

    int sock = getSocket();
    char* filename = argv[2];

    readSocket(sock, dest_sock, socklen, filename);

    return EXIT_SUCCESS;
}