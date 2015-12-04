#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "list.h"
void file83(int f_count, char** f_arr, char* f_n, char temp[12]){
    int i,j=8,pos,count=1,flag = 0;
    
    for (pos=0; pos<strlen(f_n); pos++)
        if (f_n[pos] == '.'){
            flag = 1;
            break;
        }
    
    if (flag){
        if (pos > 8){
            for (i=0; i<6; i++)
                temp[i] = (char)toupper((int)f_n[i]);
            temp[6] = '~';
            temp[7] = (char)(count + 48); 
            for (i = pos; i<strlen(f_n); i++){
                temp[j] = f_n[i];
                j++;
            }
        }
        else{
            for (i=0; i<pos+4; i++)
                temp[i] = (char)toupper((int)f_n[i]);
               
            for (i=pos+4; i<11; i++)
                temp[i] = '\0';
        }
    }
    else{
        if (strlen(f_n)>8){
            for (i=0; i<6; i++)
                temp[i] = (char)toupper((int)f_n[i]);
            temp[6] = '~';
            temp[7] = (char)(count + 48);
            for (i=8;i<12;i++)
                temp[i]='\0';
        }
        else{
            for (i=0; i<strlen(f_n); i++)
                temp[i] = (char)toupper((int)f_n[i]);
            for (i=strlen(f_n); i<11; i++)
                temp[i] = '\0';
        }
    }
}


void list_file(int arg_count, char** args){
	DIR *dir;
	struct dirent *files;
	struct stat f_stat;
	int pos,f_count= 1;
	char buff[512];
    char *file_name_arr[512];
    char f_name[12];
	for (pos=0; pos < arg_count; pos++)
		if (!strcmp(args[pos],"-l"))
			break;
	
	dir = opendir(args[pos+1]);
    while((files = readdir(dir)) != NULL){
        printf("%d, ",f_count);
        sprintf(buff, "%s/%s", args[pos+1], files->d_name);
        stat(buff, &f_stat);
        file83(f_count, file_name_arr, files->d_name,f_name);
        printf(" %s, %zu\n", f_name,f_stat.st_size);
        f_count++;
    }
    closedir(dir);
}
