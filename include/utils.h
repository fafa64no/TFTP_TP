#pragma once

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <errno.h>

#define DEFAULT_PORT "1069"

#define MAX_MSG_LENGTH 1024
#define MAX_PACKET_SIZE 516
#define MAX_BLOCK_SIZE 512
#define MAX_PACKET_AMOUNT 1024

#define OPCODE_RRQ 1
#define OPCODE_WRQ 2
#define OPCODE_DATA 3
#define OPCODE_ACK 4
#define OPCODE_ERROR 5