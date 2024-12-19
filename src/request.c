#include "request.h"

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
    char* requestBuffer = (char*) malloc(requestSize);

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