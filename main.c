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
    {"mkdir", make_dir},
    {"rmdir", remove_dir},
    {"rm", remove_file},
    {"cp", copy_files},
    {"mv", move_files},
    {"pwd", print_cdirectory},
    {"cd", change_directory},
    {"clr", clear},
    {"echo", echo}
};

// Code functions
struct command split_command(char *input) {
    struct command NEW_COMMAND = {};

    char *command = strtok(input, " ");
    char *argument = strtok(NULL, " ");

    if (command != NULL) {
        NEW_COMMAND.com = strdup(command);
    } else {
        perror("failed, null pointer detected, no initial command has been inserted: see command");
        free(command);
    }

    if (argument != NULL) {
        NEW_COMMAND.arg = strdup(argument);
    } else {
        perror("failed, null pointer detected, no initial command has been inserted: see argument");
        free(argument);
        NEW_COMMAND.arg = NULL;
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
        if (strcmp(user_command.com, &CommandsList->cmd[i]) == 0) {
            CommandsList[i].func(user_command.arg);
        }
    }
    free(user_command.com);
    free(user_command.arg);
}

// ls command
void list(const char *path) {
    struct dirent *entry;
    if (path == NULL) {
        perror("No path found\n");
        return;
    }
    DIR *dP = opendir(path);

    // check if the directory got opened successfully
    if (dP == NULL) {
        perror("opendir");
        return;
    }

    // Print the folder|directory name
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
    printf("\033[2J");
    printf("\033[3J");
    printf("\033[H");
}

void echo(const char *arg) {
    printf("%s", arg);
}

void print_cdirectory(const char *arg) {
    char *current_working_directory = getcwd(NULL, 0);
    printf("%s", current_working_directory);
}

void change_directory(const char *path) {
    if (path == NULL) {
        printf("No path found\n");
    }
}

int main(void) {
    clear("");
    // ReSharper disable once CppDFAEndlessLoop
    while (1) {
        printf("\n$ ");

        char *input = malloc(sizeof(char *) * MAX_COMMAND_LENGTH);
        fgets(input, MAX_COMMAND_LENGTH, stdin);
        exec_command(input);
        free(input);
    }
}
