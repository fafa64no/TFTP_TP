#include "fileReader.h"

char* readFile(char* filename, ssize_t* fileSize) {
    char* fileBuffer = (char*) malloc(MAX_FILE_SIZE * sizeof(char));

    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        char errorMsg[MAX_MSG_LENGTH] = {0};
        sprintf(errorMsg,"ERROR : Couldn't open file :\t%d\n",errno);
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
    *fileSize = read(fd, fileBuffer, MAX_FILE_SIZE);
    close(fd);

    if(*fileSize < 0) {
        char errorMsg[MAX_MSG_LENGTH] = {0};
        sprintf(errorMsg,"ERROR : Error while reading file :\t%d\n",errno);
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }

    return fileBuffer;
}