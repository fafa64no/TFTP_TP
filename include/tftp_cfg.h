#pragma once

#include <netdb.h>

#include "utils.h"

struct addrinfo getAddrCfg(int argc, char** argv);

void checkAddrInfoRet(int ret);

void dispAddrInfo(struct addrinfo* addrinfo);