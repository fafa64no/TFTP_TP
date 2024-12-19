#include "socketSend.h"

void sendRequest(char* request, ssize_t requestSize, int source, struct addrinfo* dest) {
    ssize_t retRequest = sendto(
        source,
        (const void*) request,
        requestSize,
        0,      // flags
        (const struct sockaddr*) dest->ai_addr,
        dest->ai_addrlen
    );

    if (retRequest < 0) {
        char errorMsg[MAX_MSG_LENGTH] = {0};
        sprintf(errorMsg,"ERROR : sendto() error :\t%d\n",errno);
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
}

void sendRequest_RRQ(int source, struct addrinfo* dest, char* filename) {
    ssize_t requestSize = getRequestSize(filename);
    char* requestBuffer = getRequest(filename, OPCODE_RRQ);
    sendRequest(requestBuffer, requestSize, source, dest);
    free(requestBuffer);
}

void sendRequest_WRQ(int source, struct addrinfo* dest, char* filename) {
    ssize_t requestSize = getRequestSize(filename);
    char* requestBuffer = getRequest(filename, OPCODE_WRQ);
    sendRequest(requestBuffer, requestSize, source, dest);
    free(requestBuffer);
}

void sendACK(int source, struct addrinfo* dest, unsigned int block) {
    ssize_t ackSize = 4 * sizeof(char);
    char* ackBuffer = (char*) malloc(ackSize);
    unsigned short block1 = block / 256;
    unsigned short block0 = block - (block / 256);
    ackBuffer[0] = 0;
    ackBuffer[1] = OPCODE_ACK;
    ackBuffer[2] = block1;
    ackBuffer[3] = block0;
    sendRequest(ackBuffer, ackSize, source, dest);
    free(ackBuffer);
}

void sendData(char* input, ssize_t inputSize, int source, struct addrinfo* dest, unsigned int block) {
    ssize_t dataBufferSize = inputSize + 4;
    char* dataBuffer = (char*) malloc(dataBufferSize * sizeof(char));
    unsigned short block1 = block/256;
    unsigned short block0 = block - (block/256);
    dataBuffer[0] = 0;
    dataBuffer[1] = OPCODE_DATA;
    dataBuffer[2] = block1;
    dataBuffer[3] = block0;
    strncpy(&dataBuffer[4], input, inputSize);
    sendRequest(dataBuffer, dataBufferSize, source, dest);
    free(dataBuffer);
}