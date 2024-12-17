#include "socket.h"

int getSocket() {
    int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    checkSocket(sock);

    return sock;
}

void checkSocket(int sock) {
    if (sock < 0) {
        const char errorMsg[] = "ERROR : Socket error\n";
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
}