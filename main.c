#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <dirent.h>
#include <unistd.h>

/* BOOLEANS */
#define true 1
#define false 0

typedef struct 
{
    int process_id;
} id;

void process_execution(int id)
{
    fork();
}
void REDIRECTION();
void SCRIPTING();

void ERROR_QUIT(char *CURRENT_COMMAND)
{
    printf("failed %s", CURRENT_COMMAND);
    
}

void err_sys(char *string)
{
    printf("%s", string);
}

void PROCESS_PID()
{

    printf("PID %ld\n", (long)getpid());
}

void list_directories()
{

}

char *save_variable(char* command, char *argv)
{
    char *variable = (char *)malloc(sizeof(char));

    if (strcmp(argv[0], "$") == 0)
    {
        while(*argv != ("/0"))
        {
                        
        }
    }
}

void ECHO_INPUT(char *command, char *argv)
{
    if (strcmp(command, "echo") == 0)
    {
        printf("argv");
    }
}

int main(int argc, char *argv[]) {

    int i = getpid();
    printf("%d", i);

    return 0;
}
