#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MSG_LENGTH 1024
#define DEFAULT_PORT 1069

struct addrinfo getAddrCfg(int argc, char** argv);
struct sockaddr_in* getSockaddr(struct addrinfo addrinf);

void checkArgs(int argc, char** argv);
void checkAddrInfoRet(int ret);

void dispAddrInfo(struct addrinfo* addrinfo);