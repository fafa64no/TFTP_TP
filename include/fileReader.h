#pragma once

#include <fcntl.h>

#include "utils.h"

#define MAX_FILE_SIZE 65536
#define MAX_MSG_LENGTH 1024

char* readFile(char* filename, ssize_t* fileSize);