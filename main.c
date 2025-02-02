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

typedef struct 
{
    int process_id;
} id;

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


}


char *save_variable(char* command, char *argv)
{
    char *variable = (char *)malloc(sizeof(char));
    char *input = readline();

    if (strcmp(argv[0], "$") == 0)
    {
        while(*argv != ("/0"))
        {
                        
        }
    }
}

void echo(char *command, char *argv)
{
    if (strcmp(command, "echo") == 0)
    {
        printf("argv");
    }
}

int main(int argc, char *argv[]) 
{

    
    return 0;
}
