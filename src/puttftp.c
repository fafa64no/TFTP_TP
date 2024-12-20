#include "puttftp.h"

int main(int argc, char** argv) {
    checkArgsPutTFTP(argc);
    dispGoalPutTFTP(argv);

    struct addrinfo dest = getAddrCfg(argc, argv);
    int source = getSocket();
    
    char* sourceFilename = argv[3];
    char* destFilename = argv[2];

    writeSocket(source, &dest, sourceFilename, destFilename);

    dispBuffer("\n", strlen("\n"));
    return EXIT_SUCCESS;
}