#include "socket.h"

int getSocket() {
    int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    checkSocket(sock);
    return sock;
}

void sendRequest_RRQ(int source, struct addrinfo* dest,  char* filename) {
    ssize_t requestSize = getRequestSize(filename);
    char* requestBuffer = getRequest_RRQ(filename);

    ssize_t retSnd = sendto(
        source,
        (const void*) requestBuffer,
        requestSize,
        0,      // flags
        (const struct sockaddr*) dest->ai_addr,
        dest->ai_addrlen
    );

    if (retSnd < 0) {
        char errorMsg[MAX_MSG_LENGTH] = {0};
        sprintf(errorMsg,"ERROR : sendto() error :\t%d\n",errno);
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
}

void readSocket(int source, struct addrinfo* dest,  char* filename) {
    ssize_t requestSize = getRequestSize(filename);
    char* requestBuffer = getRequest_RRQ(filename);

    sendRequest_RRQ(source, dest, filename);

    char* rcvBuffer = (char*) malloc(MAX_PACKET_SIZE * sizeof(char));
    socklen_t sourceAddressSize = dest->ai_addrlen;
    ssize_t retRcv;
    retRcv = recvfrom(
        source,
        rcvBuffer,
        MAX_PACKET_SIZE,
        0,      // flags
        (struct sockaddr*) dest->ai_addr,
        &sourceAddressSize
    );

    if (retRcv < 0) {
        char errorMsg[MAX_MSG_LENGTH] = {0};
        sprintf(errorMsg,"ERROR : recvfrom() error :\t%d\n",errno);
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }

    write(STDOUT_FILENO,rcvBuffer,retRcv);
}

void checkSocket(int sock) {
    if (sock < 0) {
        const char errorMsg[] = "ERROR : Socket creation error\n";
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
}