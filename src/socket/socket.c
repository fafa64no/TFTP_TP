#include "socket.h"

int getSocket() {
    int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        const char errorMsg[] = "ERROR : Socket creation error\n";
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
    return sock;
}

void readSocket(int source, struct addrinfo* dest,  char* filename) {
    sendRequest_RRQ(source, dest, filename);

    char* rcvBuffer = (char*) malloc(MAX_BLOCK_SIZE * MAX_PACKET_AMOUNT * sizeof(char));
    ssize_t retRcv, rcvBufferSize = 0;

    for (int currBlock = 1; currBlock < MAX_PACKET_AMOUNT + 1; currBlock++) {
        while(receiveData(&rcvBuffer[rcvBufferSize], &retRcv, source, dest) != currBlock);
        rcvBufferSize += retRcv;
        sendACK(source, dest, currBlock);
        if (retRcv != MAX_BLOCK_SIZE) break;
    }

    write(STDOUT_FILENO,rcvBuffer,rcvBufferSize);
    write(STDOUT_FILENO,"\n",strlen("\n"));

    free(rcvBuffer);
}

void writeSocket(int source, struct addrinfo* dest, char* sourceFilename, char* destFilename) {
    ssize_t sourceFileLength;
    char* sourceFile = readFile(sourceFilename, &sourceFileLength);

    sendRequest_WRQ(source, dest, destFilename);
    while(receiveACK(source, dest) != 0);

    int packetAmount = 1 + sourceFileLength/MAX_PACKET_SIZE;
    ssize_t lastPacketSize = sourceFileLength - (packetAmount - 1) * MAX_PACKET_SIZE;

    {
        const char msg[] = "Sending data ...\n";
        write(STDOUT_FILENO,msg,strlen(msg));
    }

    for (unsigned int i_packet = 1; i_packet <= packetAmount; i_packet++) {
        ssize_t packetSize = (i_packet == packetAmount) ? lastPacketSize : MAX_PACKET_SIZE;
        while(receiveACK_2(source, dest) != i_packet) {
            sendData(&sourceFile[(i_packet - 1) * MAX_PACKET_SIZE], packetSize, source, dest, i_packet);
        }
        const char msg[] = "\tsending more data ...\n";
        write(STDOUT_FILENO,msg,strlen(msg));
    }
}

