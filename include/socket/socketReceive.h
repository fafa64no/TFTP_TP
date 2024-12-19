#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#include "utils.h"

unsigned short receivePacket(char* packet, ssize_t* packetSize, int source, struct addrinfo* dest);
unsigned int receiveData(char* data, ssize_t* dataSize, int source, struct addrinfo* dest);
unsigned int receiveACK(int source, struct addrinfo* dest);
