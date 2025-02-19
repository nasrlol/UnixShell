#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_HISTORY 100
#define MAX_COMMAND_LENGTH 255 // not setting a  macro for the argument because they are included in the command
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

// shell commands functions prototypes
void list(const char *path);

void make_dir(const char *path);

void remove_dir(const char *path);

void remove_file(const char *path);

void copy_files(const char *arg);

void move_files(const char *arg);

void print_cdirectory(const char *arg);

void change_directory(const char *path);

void clear(const char *arg);

void echo(const char *arg);

struct exec_command CommandsList[] = {
    {"ls", list},
    {"make_dir", make_dir},
    {"remove_dir", remove_dir},
    {"remove_file", remove_file},
    {"copy_files", copy_files},
    {"move_files", move_files},
    {"print_cdirectory", print_cdirectory},
    {"change_directory", change_directory},
    {"clear", clear},
    {"echo", echo}
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
void list(const char *path) {
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

void make_dir(const char *path) {
    printf("made a new directory");
}

void remove_dir(const char *path) {
    printf("removed a directory");
}

void remove_file(const char *path) {
    printf("remove_file");
}

void copy_files(const char *arg) {
    printf("copy file");
}

void move_files(const char *arg) {
    printf("move file");
}

void clear(const char *arg) {
    if (arg != NULL) {
        printf("clear doesn't support any arguments, see help() for help");
        return;
    }

    // clear the visible part of the terminal -> see man pages clear command
    printf("\033[2J");
    // clear the input buffer of the terminal -> see man pages clear command
    printf("\033[3J");
}

void echo(const char *arg) {
    printf("%s", arg);
}

void print_cdirectory(const char *arg) {
    if (arg != NULL) {
        printf("print_cdirectory doesn't support any arguments, see help() for help");
        return;
    }
    char *current_working_directory = getcwd(NULL, 0);
    printf("%s", current_working_directory);
}

void change_directory(const char *path) {
    if (path == NULL) {
        printf("No path found\n");
    }
}

int main(void) {
    clear(NULL);
    // ReSharper disable once CppDFAEndlessLoop
    while (1) {
        printf("\n$ ");

        char *input = malloc(sizeof(char *) * MAX_COMMAND_LENGTH);
        fgets(input, MAX_COMMAND_LENGTH, stdin);
        exec_command(input);
    }
}
