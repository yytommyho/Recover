#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "valid.h"

int validChar(char ch) {
    int i, isValid = 0;
    if (ch == 33 || ch == 45 || ch == 123)
        isValid = 1;
    else if (ch >= 35 && ch <= 39)
        isValid = 1;
    else if (ch >= 40 && ch <= 41)
        isValid = 1;
    else if (ch >= 94 && ch <= 95)
        isValid = 1;
    else if (ch >= 125 && ch <= 126)
        isValid = 1;
    else if (ch >= 65 && ch <= 90)
        isValid = 1;
    else if (ch >= 48 && ch <= 57)
        isValid = 1;
    else
        return 0;

    return isValid;
}

int validFn(char target[]) {
    int i, j;
    int tokenNo = 0, isValid = 0, fnNo, extNo;
    char *fn[1023], *token;

    if (strcmp(target, "/") == 0)
        return 1;
    else if ((strcmp(target, "-d") == 0) || (strcmp(target, "-l") == 0) || (strcmp(target, "-r") == 0) || (strcmp(target, "-o") == 0))
        return 0;

    token = strtok(target, "/\"");

    while (token != NULL) {
        fn[tokenNo++] = token;
        token = strtok(NULL, "/\"");
    }

    for (i = 0; i < tokenNo; i++) {
        fnNo=0,extNo=0;
        //Cannot exceed 12 chars
        if (strlen(fn[i]) > 12)
            return 0;
            //Cannot begin with "."
        else if (fn[i][0] == '.')
            return 0;
            //check each characters
        else {
            //No. of chars of name
            for (j = 0; j < strlen(fn[i]) && fn[i][j] != '.'; j++) {
                if (validChar(fn[i][j]) == 0)
                    return 0;
                else
                    fnNo++;
            }

            //No. of chars of extensions
            if (strlen(fn[i]) != j)
                for (j = strlen(fn[i]) - 1; fn[i][j] != '.'; j--) {
                    if (validChar(fn[i][j]) == 0)
                        return 0;
                    else
                        extNo++;
                }

            if (fnNo > 8){
                printf("Bye1\n");
                return 0;
            }
            else
                isValid = 1;

            if (extNo > 3){
                printf("Bye2\n");
                return 0;
            }
            else
                isValid = 1;
        }
    }
    return isValid;
}

int isInvalidArg(int argc, char **argu) {
    
    int invalidType;

    if (argc < 4|| argc > 7)
        invalidType = 3;
    else if ((strcmp(argu[1], "-d") == 0)&&(strcmp(argu[3], "-l") == 0)) {
        if(argu[4]==NULL)
            return 1;
        else if(validFn(argu[4])==1){
             invalidType=0;
        }else
             return -1;
    } else if ((strcmp(argu[1], "-d") == 0)&&(strcmp(argu[3], "-r") == 0)&&(strcmp(argu[5], "-o") == 0)) {
        printf("Hi\n");
        if(argu[6]==NULL)
            return 2;
        else if((validFn(argu[4])==1)&&(validFn(argu[6])==1))
            invalidType=0;
        else
            return -1;
    }else
        invalidType = 3;
    return invalidType;
}