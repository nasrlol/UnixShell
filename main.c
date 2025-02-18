#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_HISTORY 100
#define MAX_COMMAND_LENGTH 255

struct com_struct {
    char *com;
    char *arg;
    int error; // 0: okay 1: not okay
};

void test() {
    printf("\nprint to output");
}

// ls command
// get the requested path and put it into a const later on when getting the user input

void ls(const char *path) {
    struct dirent *entry;
    if (path == NULL) {
        printf("No path found\n");
        return;
    }
    DIR *dP = opendir(path);

    // check if the directory got opened successfully
    if (dP == NULL) {
        perror("opendir");
        return;
    }

    // print the folder|directory name
    while ((entry = readdir(dP)) != NULL) {
        char *temporary_variable = entry->d_name;
        printf("%s\n", entry->d_name);
    }
    closedir(dP);
}

struct com_struct split_command(char *input) {
    struct com_struct NEW_COMMAND = {};

    char *command = strtok(input, " ");
    char *argument = strtok(NULL, " ");


    if (command != NULL) {
        NEW_COMMAND.com = strdup(command);
    } else {
        printf("failed, null pointer detected, no initial command has been inserted");
        free(command);
    }

    if (argument != NULL) {
        NEW_COMMAND.arg = strdup(argument);
    } else {
        printf("failed, null pointer detected, no argument has been added");
        free(argument);
    }

    return NEW_COMMAND;
}

void clear() {
    // clear the visible part of the terminal -> see man pages clear command
    printf("\033[2J");
    // clear the input buffer of the terminal -> see man pages clear command
    printf("\033[3J");
}

void change_directory(const char *path) {
    if (path == NULL) {
        printf("No path found\n");
        return;
    }
}

int main(void) {
    clear();
    while (1) {
        printf("\n$ ");

        char *input = malloc(sizeof(char *) * MAX_COMMAND_LENGTH);
        fgets(input, MAX_COMMAND_LENGTH, stdin);

        const struct com_struct new_input = split_command(input);

        new_input.com[strcspn(new_input.com, "\n")] = '\0';

        if (new_input.arg != NULL) {
            new_input.arg[strcspn(new_input.arg, "\n")] = '\0';
        }

        if (strcmp(new_input.com, "exit") == 0) {
            free(input);
            return 0;
        }
        if (strcmp(new_input.com, "ls") == 0) {
            ls(new_input.arg);
            free(new_input.com);
            free(new_input.arg);
        }
        if (strcmp(new_input.com, "echo") == 0) {
            printf("%s", new_input.arg);
            free(new_input.arg);
        }
    }
}
