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


void test_print()
{
    printf("print to output");
}

// DEFAULT SHELL COMMANDS
// exit() command
void exit_program()
{
        exit(0);
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

void print_working_directory()
{
    char current_working_directory[100];
    
    if(getcwd(current_working_directory, sizeof(current_working_directory) != 0))
    {
        printf("%s", current_working_directory);
    }
    else
    {
        perror("getcwd() error");
    }
}

// echo emulation command, without variables
void echo(char *command, char *argv)
{
    if (strcmp(command, "echo") == 0)
    {
        printf("argv");
    }
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

//    if (line_read && *line_read)
//      save_history(line_read);

    return line_read;
}


int main(void) 
{
    char *input = malloc(sizeof(char *) * MAX_COMMAND_LENGTH);    
    while (true)
    {
        printf("\nSHELL> ");
        scanf("%s", input);

        if (strcmp(input, "exit") == 0)
            exit_program();
        else if(strcmp(input, "current_directory") == 0)
            print_working_directory();
        else if(strcmp(input, "test") == 0)
            test_print();
    }

    return 0;
}
