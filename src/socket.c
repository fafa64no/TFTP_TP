#include "socket.h"

int getSocket() {
    int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    checkSocket(sock);
    return sock;
}

char* getRequestMode() {
    char mode[] = "octet";
    char* out = (char*) malloc(sizeof(char)*strlen(mode));
    strncpy(out,mode,strlen(mode));
    return (char *)out;
}

ssize_t getRequestSize(char* filename) {
    char* mode = getRequestMode();
    ssize_t requestSize = sizeof(char) * (4 + strlen(filename) + strlen(mode));
    return requestSize;
}

char* getRequest(char* filename, unsigned short opcode) {
    char* mode = getRequestMode();
    ssize_t requestSize = getRequestSize(filename);
    char* requestBuffer = (char*) malloc(requestSize + sizeof(char));

    int pos=0;
    requestBuffer[pos++]=0;
    requestBuffer[pos++]=opcode;
    sprintf(&requestBuffer[pos],"%s",filename);    pos+=strlen(filename);
    requestBuffer[pos++]=0;
    sprintf(&requestBuffer[pos],"%s",mode);        pos+=strlen(mode);
    requestBuffer[pos++]=0;

    return requestBuffer;
}

char* getRequest_RRQ(char* filename) {
    return getRequest(filename, (unsigned short) 1);
}

char* getRequest_WRQ(char* filename) {
    return getRequest(filename, (unsigned short) 2);
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

    char* rcvBuffer = (char*) malloc(2048*sizeof(char));
    ssize_t retRcv = sendto(
        source,
        (void*) rcvBuffer,
        156,
        0,      // flags
        (const struct sockaddr*) dest,
        destLen
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