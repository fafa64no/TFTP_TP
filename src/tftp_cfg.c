#include "tftp_cfg.h"

struct addrinfo getAddrCfg(int argc, char** argv) {
    checkArgs(argc, argv);

    char* host = argv[1];
    char* filename = argv[2];

    struct addrinfo hints = {0},* res, * current;
    hints.ai_protocol = IPPROTO_UDP;    // TFTP implies UDP

    int ret = getaddrinfo(host, NULL, &hints, &res);
    checkAddrInfoRet(ret);

    dispAddrInfo(res);

    return res[0];
}

void checkArgs(int argc, char** argv) {
    if (argc != 3) {
        const char errorMsg[] = "ERROR : Wrong arg count \n\tRequires two args \"host\" and \"file\"\n";
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
}

void checkAddrInfoRet(int ret) {
    if(ret != 0) {
        char errorMsg[MAX_MSG_LENGTH] = {0};
        sprintf(errorMsg,"ERROR : in getaddrinfo()\n\t%s\n",gai_strerror(ret));
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
}

void dispAddrInfo(struct addrinfo* addrinfo) {
    struct addrinfo* current = addrinfo;
    while(current != NULL) {
        char msg[MAX_MSG_LENGTH] = {0};
        sprintf(msg,
            "\t- ai_family   : %d\n"
            "\t  ai_socktype : %d\n"
            "\t  ai_protocol : %d\n\n"
            ,current->ai_family
            ,current->ai_socktype
            ,current->ai_protocol
        );
        write(STDOUT_FILENO,msg,strlen(msg));
        current = current->ai_next;
    }
}