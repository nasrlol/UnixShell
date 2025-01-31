#include <stdio.h>
#include <stdlib.h>


#include <string.h>
#include <ctype.h>

#include <readline/readline.h>

// import files for reading the current directory
#include "apue.c"
#include <dirent.h>

#define true 1
#define false 0

void err_quit(char * str) {
    printf("%s", str);
}
void err_sys(char * str) {
    printf("%s", str);
}

void PROCESS_PID(char *string) {

    printf("PID %ld\n", (long)getpid());
}

void LIST_CURRENT_DIRECTORY(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *dirp;
    if (argc != 2)
        err_quit("usage: ls directory_name");
    if ((dp = opendir(argv[1])) == NULL)
        err_sys(  argv[1]);
    while ((dirp = readdir(dp)) != NULL)
        printf("%s\n", dirp->d_name);
    closedir(dp);
}


int main(int argc, char *argv[]) {

    printf("succefully started the program");
    // RUNNING THE PROGRAM ON AN ENDLESS LOOP
    // BREAKS WHEN USER ENTERS EXIT
    // ReSharper disable once CppDFAEndlessLoop

    return 0;
}
