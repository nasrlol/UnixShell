#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_HISTORY 100
#define MAX_COMMAND_LENGTH 255 // not setting a  macro for the argument because they are included in the command)
#define MAX_PATH_LENGTH 1024

struct command {
    char *com;
    char *arg;
};

struct exec_command {
    const char *cmd;
    void (*func)(const char *);
};


// code prototype functions
struct command split_command(char *input);

void exec_command(char *input);

// code functions
struct command split_command(char *input) {
    struct command NEW_COMMAND = {};

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
        free(argument);
    }
    return NEW_COMMAND;
}

void exec_command(char *input) {
    struct command NEW_COMMAND = {};

    // cycle through the command array and find the matching command and execute it
}


// shell commands functions prototypes
void list(const char *path);

void make_dir(const char *path);

void remove_dir(const char *path);

void remove_file(const char *path);

void copy_files(const char *source, const char *dest);

void move_files(const char *source, const char *dest);

char *print_cdirectory();

void change_directory(const char *path);

void clear();


struct exec_command CommandsList[] = {
    {"ls", ls},
};

// code functions
struct command split_command(char *input) {
    struct command NEW_COMMAND = {};

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
        free(argument);
    }
    return NEW_COMMAND;
}

void exec_command(char *input) {
    const struct command user_command = split_command(input);
    user_command.com[strcspn(user_command.com, "\n")] = '\0';
    if (user_command.arg != NULL) {
        user_command.arg[strcspn(user_command.arg, "\n")] = '\0';
    }

    for (int i = 0; i < sizeof(*CommandsList) / sizeof(CommandsList->cmd[0]); i++) {
        // ReSharper disable once CppIncompatiblePointerConversion
        if (strcmp(user_command.com, &CommandsList->cmd[i]) == 0) {
            CommandsList[i].func(user_command.arg);
        }
    }
}

// shell command functions
// ls command
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
        printf("%s\n", entry->d_name);
    }
    closedir(dP);
}

void clear() {
    // clear the visible part of the terminal -> see man pages clear command
    printf("\033[2J");
    // clear the input buffer of the terminal -> see man pages clear command
    printf("\033[3J");
}

char *print_cdirectory() {
    char *current_working_directory = getcwd(NULL, 0);
    /* getcwd() command already allocates malloc for the path that should be returned,
     to do: should I free it when finished or not?/
      so what I understand from the documentation, you should only free it when actually setting an exact size
      but when keeping the max size to 0 and relying on the malloc there is no need for it
      not sure though
      should rely on further debugging
     */

    return current_working_directory;
}

void change_directory(const char *path) {
    if (path == NULL) {
        printf("No path found\n");
    }
}

int main(void) {
    clear();
    while (1) {
        printf("\n$ ");

        char *input = malloc(sizeof(char *) * MAX_COMMAND_LENGTH);
        fgets(input, MAX_COMMAND_LENGTH, stdin);

        const struct command new_input = split_command(input);
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
            if (new_input.arg != NULL) {
                free(new_input.arg);
            }
        }
        if (strcmp(new_input.com, "echo") == 0) {
            printf("%s", new_input.arg);
            free(new_input.arg);
        }
        if (strcmp(new_input.com, "clear") == 0) {
            clear();
        }
    }
}
