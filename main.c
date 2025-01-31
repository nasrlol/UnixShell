#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <dirent.h>
#include <unistd.h>

#define true 1
#define false 0

void PROCESS_PID()
{
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

void ECHO_INPUT(char *string)
{
    printf("%s", string);
}

int loop_shell()
{

    
    return 0;
}

int main(int argc, char *argv[]) {

    int c; 
    while ((c = getc(stdin) != EOF))
    {
        if put
    }
    LIST_CURRENT_DIRECTORY(argc, argv);
    printf("successfully started the program");

    return 0;
}
