#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_HISTORY 100
#define MAX_COMMAND_LENGTH 256

struct com_struct {
    char *com;
    char *arg;
};

void test() {
    printf("\nprint to output");
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
        printf("%s", entry->d_name);
    }
    closedir(dP);
}

// echo command
char *echo(const char *command) {
    const char *argv = (char *) malloc(sizeof(char) * 4);
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

    const char *command = strtok(input, "");
    const char *argument = strtok(NULL, "\n");

    NEW_COMMAND.com = command ? strdup(command) : NULL;
    NEW_COMMAND.arg = command ? strdup(argument) : NULL;

    return NEW_COMMAND;
}

int main(void) {
    while (1) {
        char *input = malloc(MAX_COMMAND_LENGTH);

        // print the shell sign
        printf("\n $ ");

        // get the user input, store it and split it up
        fgets(input, MAX_COMMAND_LENGTH, stdin);
        const struct com_struct new_input = split_command(input);

        if (strcmp(new_input.com, "ls") == 0) {
            ls(new_input.arg);
        } else if (strcmp(new_input.com, "test") == 0) {
            test();
        } else if (strcmp(new_input.com, "exit") == 0) {
            free(input);
            free(new_input.com);
            free(new_input.arg);
            exit_();
        }
    }
    return 0;
}
