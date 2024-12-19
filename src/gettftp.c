#include "gettftp.h"

int main(int argc, char** argv) {
    checkArgsGetTFTP(argc);
    
    struct addrinfo dest = getAddrCfg(argc, argv);
    int source = getSocket();

    char* filename = argv[2];

    readSocket(source, &dest, filename);

    return EXIT_SUCCESS;
}