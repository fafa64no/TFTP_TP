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

int getSocket();
void checkSocket(int sock);

char* getRequestMode();
ssize_t getRequestSize(char* filename);
char* getRequest(char* filename, unsigned short opcode);
char* getRequest_RRQ(char* filename);
char* getRequest_WRQ(char* filename);

void readSocket(int source, struct sockaddr_in* dest, ssize_t destLen, char* filename);