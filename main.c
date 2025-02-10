#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdbool.h>
#include <linux/limits.h>

#define MAX_HISTORY 100
#define MAX_COMMAND_LENGTH 256

// static int CURRENT_COMMAND_INDEX = 0;
// static int CURRENT_HISTORY_INDEX = 0;
// static char *COMMAND_HISTORY[MAX_HISTORY] = { NULL};


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

// ls command
void list_current_directories()
{
    fork();

    DIR *DIRECTORY_STREAM;
    DIRECTORY_STREAM = opendir(".");

    if (DIRECTORY_STREAM == NULL)
    {
        perror("ERROR_DIRECTORY_STREAM_EMPTY");
    }
    else
        printf("%p", (&DIRECTORY_STREAM));
    _exit(0); 

}

char *print_working_directory()
{
    char *current_working_directory = malloc(sizeof(char) * 100);
    
    if(getcwd(current_working_directory, sizeof(current_working_directory) != 0))
    {
        return current_working_directory;
    }
    else
    {
        perror("getcwd() error");
        return "ERROR";
    }
}

// echo emulation command, without variables
char *echo(char *command)
{
    char *argv = (char *)malloc(sizeof(char) * 4);
    char *command_argument = (char *)malloc(sizeof(char) * 100); 

    int separation_index = 0;
    for (int i = 0; i < sizeof(command); i++)
    {
        if (strcmp(&command[i], " ") == 0)
        {
            separation_index = i;

            for ( int j = 0; j < separation_index; j++)
            {
                argv = &command[j];
            }
        }
    }
    if (strcmp(argv, "echo") == 0)
    {
        
        for (int i = separation_index + 1; i < (sizeof(command) - separation_index); i++)  
        {
             if(strcmp(&command[i], "\0") != 0)
             {
                 break;
             }
             else
             {
                 strcpy(&command_argument[i - (separation_index - 1)], &command[i]);
             }
        }
    }
    
    return command_argument;

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
        else if(strcmp(input,"ls") == 0)
            list_current_directories();
    }

    return 0;
}
