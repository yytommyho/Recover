#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include "valid.h"
#include "list.h"
#define MAX_LENGTH 255


int main(int arg_count, char *args[]) {

    int invalidType;
    invalidType = isInvalidArg(arg_count,args);
    if (invalidType == 0) {
        list_file(arg_count,args);
    } else {
        printf("Usage:./recover -d [device filename] [other argument]\n");
        if (invalidType !=2)
            printf("-l target\t\tList the target directory\n");
        if (invalidType !=1)
            printf("-r target -o dest\tRecover the target pathname\n");
    }
    return 0;
}

