#include "gettftp.h"

int main(int argc, char** argv) {
    checkArgsGetTFTP(argc);
    dispGoalGetTFTP(argv);
    
    struct addrinfo dest = getAddrCfg(argc, argv);
    int source = getSocket();

    char* filename = argv[2];

    readSocket(source, &dest, filename);

    dispBuffer("\n\n", strlen("\n\n"));
    return EXIT_SUCCESS;
}