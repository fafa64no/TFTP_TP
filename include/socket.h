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

int getSocket();
void checkSocket(int sock);

void readSocket(int source, struct sockaddr_in* dest, ssize_t destLen, char* filename);