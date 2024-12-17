#include "tftp_cfg.h"

int getAddrCfg(int argc, char** argv) {
    checkArgs(argc, argv);

    char* host = argv[1];
    char* filename = argv[2];

    return 0;
}

void checkArgs(int argc, char** argv) {
    if (argc != 3) {
        const char errorMsg[] = "ERROR : Wrong arg count \n\tRequires two args \"host\" and \"file\"\n";
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
}