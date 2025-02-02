#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <dirent.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>


/* BOOLEANS */
#define true 1
#define false 0
#define _DEFAULT_SOURCE

void exit_program(char *argv)
{
    if (strcmp(argv, "exit"))
    {
        exit(0);
    }
}

void get_pid_parent_process()
{
    printf("PID %ld\n", (long)getpid());
}

void list_directories()
{
    struct dirent **namelist;
    int n;

    n = scandir(".", &namelist, NULL, alphasort);
    if (n == -1)
    {
        perror("scandir");
        exit(EXIT_FAILURE);
    }

    while (n--)
    {
        printf("%s\n", namelist[n]->d_name);
        free(namelist[n]);
    }
    free(namelist[n]);
    exit(EXIT_SUCCESS);
}



void echo(char *command, char *argv)
{
    if (strcmp(command, "echo") == 0)
    {
        printf("argv");
    }
}

int main(void) 
{

    char *input;
    readline(input);
     
    while(strcmp(input, "exit") != 0)
    {
        list_directories();
    }
        exit_program(input);
    
    return 0;
}
