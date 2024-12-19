#include "socketReceive.h"

unsigned short receivePacket(char* packet, ssize_t* packetSize, int source, struct addrinfo* dest) {
    socklen_t sourceAddressSize = dest->ai_addrlen;
    *packetSize = recvfrom(
        source,
        packet,
        MAX_PACKET_SIZE,
        0,      // flags
        (struct sockaddr*) dest->ai_addr,
        &sourceAddressSize
    );
    if (*packetSize < 0) {
        char errorMsg[MAX_MSG_LENGTH] = {0};
        sprintf(errorMsg,"ERROR : recvfrom() error :\t%d\n",errno);
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }

    unsigned short opcode = packet[1];
    if (opcode < 1 && opcode > 5) {
        const char errorMsg[] = "ERROR : Unknown opcode\n";
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
    if (opcode == 5) {
        write(STDOUT_FILENO, packet, *packetSize);
        exit(EXIT_FAILURE);
    }
    return opcode;
}

unsigned int receiveData(char* data, ssize_t* dataSize, int source, struct addrinfo* dest) {
    unsigned int block;
    char tmpBuffer[MAX_PACKET_SIZE];
    ssize_t tmpBufferSize;
    if (receivePacket(&tmpBuffer[0], &tmpBufferSize, source, dest) == OPCODE_DATA) {
        block = tmpBuffer[3] + 256 * tmpBuffer[2];
    } else {
        const char errorMsg[] = "ERROR : Wrong opcode received\n";
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
    *dataSize = tmpBufferSize - 4;
    strncpy(data, &tmpBuffer[4], *dataSize);
    return block;
}

unsigned int receiveACK(int source, struct addrinfo* dest) {
    unsigned int block;
    char tmpBuffer[MAX_PACKET_SIZE];
    ssize_t tmpBufferSize;
    if (receivePacket(&tmpBuffer[0], &tmpBufferSize, source, dest) == OPCODE_ACK) {
        block = tmpBuffer[3] + 256 * tmpBuffer[2];
    } else {
        const char errorMsg[] = "ERROR : Wrong opcode received\n";
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
    return block;
}
