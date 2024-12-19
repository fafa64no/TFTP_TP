#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <errno.h>

#include "request.h"
#include "tftp_cfg.h"
#include "fileReader.h"

#define MAX_MSG_LENGTH 1024
#define MAX_PACKET_SIZE 512
#define MAX_PACKET_AMOUNT 1024

#define OPCODE_RRQ 1
#define OPCODE_WRQ 2
#define OPCODE_DATA 3
#define OPCODE_ACK 4
#define OPCODE_ERROR 5

int getSocket();
void checkSocket(int sock);

void sendRequest_RRQorWRQ(int source, struct addrinfo* dest, char* filename, unsigned short opcode);
void sendRequest_RRQ(int source, struct addrinfo* dest,  char* filename);
void sendRequest_WRQ(int source, struct addrinfo* dest,  char* filename);

void sendACK(int source, struct addrinfo* dest, unsigned short block);
int receiveACK(int source, struct addrinfo* dest);
void receivePacket(char* output, ssize_t* outputSize, int source, struct addrinfo* dest);
void sendData(char* input, ssize_t inputSize, int source, struct addrinfo* dest, int block);

void readSocket(int source, struct addrinfo* dest, char* filename);
void writeSocket(int source, struct addrinfo* dest, char* sourceFilename, char* destFilename);