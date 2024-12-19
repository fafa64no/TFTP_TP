#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#include "request.h"
#include "utils.h"

void sendRequest(char* request, ssize_t requestSize, int source, struct addrinfo* dest);
void sendRequest_RRQ(int source, struct addrinfo* dest,  char* filename);
void sendRequest_WRQ(int source, struct addrinfo* dest,  char* filename);
void sendACK(int source, struct addrinfo* dest, unsigned int block);
void sendData(char* input, ssize_t inputSize, int source, struct addrinfo* dest, unsigned int block);