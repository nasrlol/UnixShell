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

struct com_struct split_command(char *input) {
    struct com_struct NEW_COMMAND;

    const char *command = strtok(input, " ");
    const char *argument = strtok(NULL, " ");

    NEW_COMMAND.com = strdup(command);
    NEW_COMMAND.arg = strdup(argument);

    return NEW_COMMAND;
}

int main(void) {
    while (1) {
        char *input = malloc(sizeof(char *) * MAX_COMMAND_LENGTH);

        printf("\n$ ");

        fgets(input, MAX_COMMAND_LENGTH, stdin);
        const struct com_struct new_input = split_command(input);

        new_input.com[strcspn(new_input.com, "\n")] = '\0';
        new_input.arg[strcspn(new_input.arg, "\n")] = '\0';

        if (strcmp(new_input.com, "exit\n") == 0) {
            exit_();
            free(input);
            free(new_input.com);
            free(new_input.arg);
            return 0;
        }
        if (strcmp(new_input.com, "ls\n") == 0) {
            printf("DETECTED LS COMMAND");
            ls(new_input.arg);
        }
        if (strcmp(new_input.com, "echo\n") == 0) {
            printf("DETECTED ECHO COMMAND");
            printf("%s", new_input.arg);
            free(new_input.arg);
        }
    }
}

