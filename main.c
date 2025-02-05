#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>


/* BOOLEANS */
#define true 1
#define false 0
#define _DEFAULT_SOURCE

#define MAX_HISTORY 10
#define MAX_COMMAND_LENGTH 256


static int CURRENT_COMMAND_INDEX            = 0;
static int CURRENT_COMMAND_HISTORY_INDEX    = 0;
static char COMMAND_HISTORY[MAX_HISTORY][MAX_COMMAND_LENGTH];



static char *line_read = (char*)NULL; 


// DEFAULT SHELL COMMANDS
// exit() command
void exit_program(char *argv)
{
    if (strcmp(argv, "exit"))
    {
        exit(0);
    }
}

// pwd command
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

// echo emulation command, without variables
void echo(char *command, char *argv)
{
    if (strcmp(command, "echo") == 0)
    {
        printf("argv");
    }
}

char *save_history(char *user_input)
{
    
    while (CURRENT_COMMAND_HISTORY_INDEX < MAX_HISTORY)
    {
        while (CURRENT_COMMAND_INDEX < MAX_COMMAND_LENGTH)
        {
            COMMAND_HISTORY[CURRENT_COMMAND_HISTORY_INDEX][CURRENT_COMMAND_INDEX] = *user_input;
            CURRENT_COMMAND_HISTORY_INDEX++;
        }
    }
    return *COMMAND_HISTORY;
}

// GET USER INPUT
char * get_line()
{
    if (line_read)
    {
        free(line_read);
        line_read = (char *)NULL;
    }
    scanf("%s", &(*line_read));

    if (line_read && *line_read)
        save_history(line_read);

    return line_read;
}


int main(void) 
{
    char *input;    
    while(strcmp(input, "exit") != 0)
    {
        list_directories();
    }
        exit_program(input);
    
    return 0;
}
