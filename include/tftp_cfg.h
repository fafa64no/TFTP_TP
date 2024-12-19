#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#include "utils.h"

void checkArgsGetTFTP(int argc);
void checkArgsPutTFTP(int argc);

struct addrinfo getAddrCfg(int argc, char** argv);

void checkAddrInfoRet(int ret);

void dispAddrInfo(struct addrinfo* addrinfo);