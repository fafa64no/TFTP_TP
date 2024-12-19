#include "socket.h"

int getSocket() {
    int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    checkSocket(sock);
    return sock;
}

void checkSocket(int sock) {
    if (sock < 0) {
        const char errorMsg[] = "ERROR : Socket creation error\n";
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
}

void sendRequest_RRQ(int source, struct addrinfo* dest, char* filename) {
    sendRequest_RRQorWRQ(source, dest, filename, OPCODE_RRQ);
}

void sendRequest_WRQ(int source, struct addrinfo* dest, char* filename) {
    sendRequest_RRQorWRQ(source, dest, filename, OPCODE_WRQ);
}

void sendRequest_RRQorWRQ(int source, struct addrinfo* dest, char* filename, unsigned short opcode) {
    ssize_t requestSize = getRequestSize(filename);
    char* requestBuffer = getRequest(filename, opcode);

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
    ackBuffer[1] = OPCODE_ACK;
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

int receiveACK(int source, struct addrinfo* dest) {
    char packetReceived[MAX_PACKET_SIZE] = {0};
    ssize_t packetReceivedSize;

    receivePacket(&packetReceived[0], &packetReceivedSize, source, dest);
    if(packetReceivedSize < 4) {
        const char errorMsg[] = "ERROR : Too small ACK\n";
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
    int opcode = packetReceived[1] + 256 * packetReceived[0];

    switch (opcode) {
    case OPCODE_ERROR:
        write(STDOUT_FILENO, packetReceived, packetReceivedSize);
        exit(EXIT_FAILURE);
    case OPCODE_ACK:
        return packetReceived[3] + 256 * packetReceived[2];
    default:
        const char errorMsg[] = "ERROR : Unknown opcode\n";
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }

    return -1;
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
    sendRequest_RRQ(source, dest, filename);

    char* rcvBuffer = (char*) malloc(MAX_PACKET_SIZE * MAX_PACKET_AMOUNT * sizeof(char));
    ssize_t retRcv, rcvBufferSize = 0;

    for (int currBlock = 1; currBlock < MAX_PACKET_AMOUNT + 1; currBlock++) {
        receivePacket(&rcvBuffer[rcvBufferSize], &retRcv, source, dest);
        rcvBufferSize += retRcv;
        sendACK(source, dest, currBlock);
        if (retRcv != MAX_PACKET_SIZE) break;
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
    printf("lastPacketSize = %ld\n",lastPacketSize);

    for (int i_packet = 1; i_packet <= packetAmount; i_packet++) {
        ssize_t packetSize = (i_packet == packetAmount) ? lastPacketSize : MAX_PACKET_SIZE;
        while(receiveACK(source, dest) != i_packet) {
            sendData(&sourceFile[(i_packet - 1) * MAX_PACKET_SIZE], packetSize, source, dest, i_packet);
        }
    }
}

void sendData(char* input, ssize_t inputSize, int source, struct addrinfo* dest, int block) {
    ssize_t dataBufferSize = inputSize + 4;
    char* dataBuffer = (char*) malloc(dataBufferSize * sizeof(char));

    unsigned int block1 = block/256;
    unsigned int block0 = block - (block/256);

    dataBuffer[0] = 0;
    dataBuffer[1] = OPCODE_DATA;
    dataBuffer[2] = block1;
    dataBuffer[3] = block0;

    strncpy(&dataBuffer[4], input, inputSize);

    ssize_t retSnd = sendto(
        source,
        (const void*) dataBuffer,
        dataBufferSize,
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

    free(dataBuffer);
}