#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include<sys/types.h>
#include <fcntl.h>
#include <string.h>
#define MAX_LENGTH 255

//Break all args and return #no of args

int command_handle(char* cmd_line, char** args) {
    int i = 1;
    cmd_line[strlen(cmd_line) - 1] = '\0';
    args[0] = strtok(cmd_line, " ");
    while ((args[i] = strtok(0, " "))) {
        i++;
    }
    return i;
}

int main() {
    //Declare in main
    char *cmd_line = malloc(sizeof (char*) * MAX_LENGTH);
    char *args[MAX_LENGTH];
    int args_count;
    int i;
    int invalidType;
    //Get User input
    if (!fgets(cmd_line, (sizeof (char*) * MAX_LENGTH), stdin))
        exit(0);
    //Get #no of args and broken args
    args_count = command_handle(cmd_line, args);
    //Show the result only
    invalidType = isInvalidArg(args_count, args);
    if (invalidType == 0) {
        printf("Right!\n");
    } else {
        printf("Usage:./recover -d [device filename] [other argument]\n");
        if (invalidType == 1 || invalidType == 3)
            printf("-l target\t\tList the target directory\n");
        if (invalidType == 2 || invalidType == 3)
            printf("-r target -o dest\tRecover the target pathname\n");
        if (invalidType == -1)
            printf("Invalid target/filename\n");
    }
    return 0;
}

