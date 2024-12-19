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

    free(requestBuffer);
}

void sendACK(int source, struct addrinfo* dest, unsigned short block) {
    ssize_t ackSize = 4 * sizeof(char);
    char* ackBuffer = (char*) malloc(ackSize);

    ackBuffer[0] = 0;
    ackBuffer[1] = 4;
    ackBuffer[2] = 0;
    ackBuffer[3] = block;

    ssize_t retSnd = sendto(
        source,
        (const void*) ackBuffer,
        ackSize,
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

    free(ackBuffer);
}

void receivePacket(char* output, ssize_t* outputSize, int source, struct addrinfo* dest) {
    socklen_t sourceAddressSize = dest->ai_addrlen;
    *outputSize = recvfrom(
        source,
        output,
        MAX_PACKET_SIZE,
        0,      // flags
        (struct sockaddr*) dest->ai_addr,
        &sourceAddressSize
    );

    if (*outputSize < 0) {
        char errorMsg[MAX_MSG_LENGTH] = {0};
        sprintf(errorMsg,"ERROR : recvfrom() error :\t%d\n",errno);
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
}

void readSocket(int source, struct addrinfo* dest,  char* filename) {
    ssize_t requestSize = getRequestSize(filename);
    char* requestBuffer = getRequest_RRQ(filename);

    sendRequest_RRQ(source, dest, filename);

    char* rcvBuffer = (char*) malloc(MAX_PACKET_SIZE * MAX_PACKET_AMOUNT * sizeof(char));
    ssize_t retRcv, rcvBufferSize = 0;

    for (int currBlock = 0; currBlock < MAX_PACKET_AMOUNT; currBlock++) {
        receivePacket(&rcvBuffer[rcvBufferSize], &retRcv, source, dest);
        rcvBufferSize += retRcv;
        sendACK(source, dest, currBlock + 1);
        if (retRcv != MAX_PACKET_SIZE) break;
    }

    write(STDOUT_FILENO,rcvBuffer,rcvBufferSize);
    write(STDOUT_FILENO,"\n",strlen("\n"));
}

void checkSocket(int sock) {
    if (sock < 0) {
        const char errorMsg[] = "ERROR : Socket creation error\n";
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
}