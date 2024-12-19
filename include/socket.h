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

#define MAX_MSG_LENGTH 1024
#define MAX_PACKET_SIZE 512

int getSocket();
void checkSocket(int sock);

void sendRequest_RRQ(int source, struct addrinfo* dest,  char* filename);
void readSocket(int source, struct addrinfo* dest, char* filename);