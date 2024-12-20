#include "utils.h"

void checkArgsGetTFTP(int argc) {
    if (argc != 3) {
        const char errorMsg[] = "ERROR : Wrong arg count \n\tRequires two args \"host\" and \"file\"\n";
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
}

void checkArgsPutTFTP(int argc) {
    if (argc != 4) {
        const char errorMsg[] = "ERROR : Wrong arg count \n\tRequires three args \"host\",  \"destination_file\" and \"source_file\"\n";
        write(STDOUT_FILENO,errorMsg,strlen(errorMsg));
        exit(EXIT_FAILURE);
    }
}

void dispGoalGetTFTP(char** argv) {
    char goalMsg[MAX_MSG_LENGTH] = {0};
    sprintf(goalMsg,
        "*** Reding %s from %s at port %s\n\n",
        argv[2],
        argv[1],
        DEFAULT_PORT
    );
    write(STDOUT_FILENO,goalMsg,strlen(goalMsg));
}

void dispGoalPutTFTP(char** argv) {
    char goalMsg[MAX_MSG_LENGTH] = {0};
    sprintf(goalMsg,
        "*** Writing %s at %s on %s at port %s\n\n",
        argv[3],
        argv[2],
        argv[1],
        DEFAULT_PORT
    );
    write(STDOUT_FILENO,goalMsg,strlen(goalMsg));
}

void dispBuffer(char* buffer, ssize_t bufferSize) {
    write(STDOUT_FILENO,buffer,bufferSize);
}