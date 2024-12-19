#pragma once

#include "tftp_cfg.h"
#include "fileReader.h"
#include "socketSend.h"
#include "socketReceive.h"
#include "utils.h"

int getSocket();

void readSocket(int source, struct addrinfo* dest, char* filename);
void writeSocket(int source, struct addrinfo* dest, char* sourceFilename, char* destFilename);

int receiveACK_2(int source, struct addrinfo* dest);