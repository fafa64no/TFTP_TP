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