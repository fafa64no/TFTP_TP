#pragma once

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#include <errno.h>

#define MAX_FILE_SIZE 65536
#define MAX_MSG_LENGTH 1024

char* readFile(char* filename, ssize_t* fileSize);