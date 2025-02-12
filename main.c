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

struct com_struct {
    char *com;
    char *arg;
};

void test() {
    printf("print to output");
}

// exit() command
void exit_() {
    exit(0);
}

// ls command
// get the requested path and put it into a const later on when getting the user input 
void ls(const char *path) {
    struct dirent *entry;
    DIR *dP = opendir(path);

    // check if the directory got opened successfully
    if (dP == NULL) {
        perror("opendir");
        return;
    }

    // print the folder|directory name
    while ((entry = readdir(dP)) != NULL) {
        printf("s\n", entry->d_name);
    }
    closedir(dP);
}

// pwd command
char *pwd() {
    char *current_working_directory = malloc(sizeof(char) * 100);

    if (getcwd(current_working_directory, sizeof(current_working_directory) != 0)) {
        return current_working_directory;
    } else {
        perror("getcwd() error");
        return "ERROR";
    }
}

// echo command
char *echo(char *command) {
    char *argv = (char *) malloc(sizeof(char) * 4);
    char *command_argument = (char *) malloc(sizeof(char) * 100);

    int separation_index = 0;
    for (int i = 0; i < sizeof(command); i++) {
        if (strcmp(&command[i], " ") == 0) {
            separation_index = i;

            for (int j = 0; j < separation_index; j++) {
                argv = &command[j];
            }
        }
    }
    if (strcmp(argv, "echo") == 0) {

        for (int i = separation_index + 1; i < (sizeof(command) - separation_index); i++) {
            if (strcmp(&command[i], "\0") != 0) {
                break;
            } else {
                strcpy(&command_argument[i - (separation_index - 1)], &command[i]);
            }
        }
    }
    return command_argument;
}

struct com_struct split_command(char *input) {

    struct com_struct NEW_COMMAND;

    char *command = (char *) malloc(sizeof(char) * 4);
    char *argument = (char *) malloc(sizeof(char) * 100);

    if (command == NULL || argument == NULL) {
        printf("found a null pointer when dynamically assigning memory to the command or variable argument");
        exit(1);
    }

    int space_position = 0;
    for (int i = 0; i < sizeof(command); i++) {
        if (strcmp(&input[i], " ") == 0) {
            space_position = i;

            for (int j = 0; j < space_position; j++) {
                command = &input[j];
            }
            for (int x = space_position; x < sizeof(input) - space_position; x++) {
                argument = &input[x];
            }
        }

    }
    NEW_COMMAND.com = command;
    NEW_COMMAND.arg = argument;

    return NEW_COMMAND;

}

int main(void) {
    char *input = malloc(sizeof(char *) * MAX_COMMAND_LENGTH);

    do {
        if (getchar()) {
            printf("\nSHELL> ");
            scanf("%s", input);

        struct com_struct new_input = split_command(input);

        if (strcmp(new_input.com, "ls") == 0) {
            char *path;
            path = (char *) malloc(sizeof(char) * 100);

            strcpy(path, new_input.arg);
            ls(path);
        } else if (strcmp(new_input.com, "test") == 0){
            test();
        }
        }
    }
    while (true);

    return 0;
}
