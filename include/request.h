#pragma once

#include "utils.h"

char* getRequestMode();
ssize_t getRequestSize(char* filename);

char* getRequest(char* filename, unsigned short opcode);
char* getRequest_RRQ(char* filename);
char* getRequest_WRQ(char* filename);