#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdbool.h>



#define MAX_HISTORY 100
#define MAX_COMMAND_LENGTH 256

static int CURRENT_COMMAND_INDEX = 0;
static int CURRENT_HISTORY_INDEX = 0;
static char *COMMAND_HISTORY[MAX_HISTORY] = { NULL};


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

char **save_history(char *user_input)
{
    char **command_history;

    for (CURRENT_HISTORY_INDEX; CURRENT_HISTORY_INDEX < MAX_HISTORY; CURRENT_HISTORY_INDEX++)
    {
        for(CURRENT_COMMAND_INDEX; CURRENT_COMMAND_INDEX < MAX_COMMAND_LENGTH; CURRENT_COMMAND_INDEX++)
            {
                command_history[CURRENT_HISTORY_INDEX][CURRENT_COMMAND_INDEX] = user_input[CURRENT_COMMAND_INDEX];  
            }
    }
    return command_history;
}

// GET USER INPUT
char * get_line()
{
    char *line_read = malloc(sizeof(char) * MAX_COMMAND_LENGTH);

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
    char *input = malloc(sizeof(char *) * MAX_COMMAND_LENGTH);    
    while (true)
    {
        scanf("%s", input);
    }

    return 0;
}
