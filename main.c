#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <dirent.h>
#include <unistd.h>

/* BOOLEANS */
#define true 1
#define false 0

/* SIGNALS */
#define SIGHUP  1   /* Hang up the process */ 
#define SIGINT  2   /* Interrupt the process */ 
#define SIGQUIT 3   /* Quit the process */ 
#define SIGILL  4   /* Illegal instruction. */ 
#define SIGTRAP 5   /* Trace trap. */ 
#define SIGABRT 6   /* Abort. */

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

void LIST_CURRENT_DIRECTORY(int argc, char *argv[])
{
    
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


    int i = getpid();
    printf("%d", i);

    return 0;
}
