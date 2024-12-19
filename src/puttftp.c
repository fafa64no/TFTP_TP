#include "puttftp.h"

int main(int argc, char** argv) {
    struct addrinfo dest = getAddrCfg(argc, argv);
    int source = getSocket();
    
    char sourceFilename[] = "data/gringo.txt";
    char* destFilename = argv[2];

    writeSocket(source, &dest, &sourceFilename[0], destFilename);

    return EXIT_SUCCESS;
}