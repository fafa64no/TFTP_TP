#include "tftp_cfg.h"

void checkArgsGetTFTP(int argc) {
    if (argc != 3) {
        const char errorMsg[] = "ERROR : Wrong arg count \n\tRequires two args \"host\" and \"file\"\n";
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
}

void checkArgsPutTFTP(int argc) {
    if (argc != 4) {
        const char errorMsg[] = "ERROR : Wrong arg count \n\tRequires three args \"host\",  \"destination_file\" and \"source_file\"\n";
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
}

struct addrinfo getAddrCfg(int argc, char** argv) {
    char* host = argv[1];
    char* filename = argv[2];

    struct addrinfo hints = {0},* res,* current;
    hints.ai_protocol = IPPROTO_UDP;    // TFTP implies UDP

    int ret = getaddrinfo(host, DEFAULT_PORT, &hints, &res);
    checkAddrInfoRet(ret);

    dispAddrInfo(res);

    return *res;
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
    const char dispMsg[] = "Found sockets : \n";
    write(STDOUT_FILENO,dispMsg,strlen(dispMsg));
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