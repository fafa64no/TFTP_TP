#include "socket.h"

int getSocket() {
    int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    checkSocket(sock);
    return sock;
}

void readSocket(int source, struct sockaddr_in* dest, ssize_t destLen,  char* filename) {
    ssize_t requestSize = getRequestSize(filename);
    char* requestBuffer = getRequest_RRQ(filename);

    ssize_t retSnd = sendto(
        source,
        (const void*) requestBuffer,
        requestSize,
        0,      // flags
        (const struct sockaddr*) dest,
        destLen
    );

    ssize_t fileSize = 128;
    char* rcvBuffer = (char*) malloc(fileSize*sizeof(char));
    socklen_t sourceAddressSize = destLen;
    ssize_t retRcv = recvfrom(
        source,
        (void*) rcvBuffer,
        fileSize,
        0,      // flags
        (struct sockaddr*) dest,
        &sourceAddressSize
    );

    printf("\nTest : %s"
        "\n\tsource = %d"
        "\n\terrno = %d"
        "\n\tretSnd = %ld"
        "\n\tretRcv = %ld"
        "\n",
        rcvBuffer,
        source,
        errno,
        retSnd,
        retRcv
    );
}

void checkSocket(int sock) {
    if (sock < 0) {
        const char errorMsg[] = "ERROR : Socket creation error\n";
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
}