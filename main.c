#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

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

struct split_arg {
    const char *source;
    const char *destination;
};

// code prototype functions
struct command split_command(char *input);

void exec_command(char *input);

void split_arg(struct command argument);

// shell commands functions prototypes
void list(const char *path);

void make_dir(const char *path);

void remove_file(const char *path);

void remove_dir(const char *path); // trying to delete the folder and the files init recursively

// void copy_files(struct split_arg argument);
void copy_files(const char *arg);

// void move_files(struct split_arg argument);
void move_files(const char* arg);

void print_cdirectory(const char *arg);

void change_directory(const char *path);

void change_ownership(const char *path);

void clear(const char *arg);

void echo(const char *arg);

void exit_(const char *arg);

struct exec_command CommandsList[] = {
    {"ls", list},
    {"mkdir", make_dir},
    {"rmdir", remove_dir},
    {"rm", remove_file},
    {"cp", copy_files},
    {"mv", move_files},
    {"chown", change_ownership},
    {"pwd", print_cdirectory},
    {"cd", change_directory},
    {"clr", clear},
    {"echo", echo},
    {"exit", exit_}
};

// Code functions
struct command split_command(char *input) {
    struct command user_command;

    const char *command = strtok(input, " ");
    const char *argument = strtok(NULL, " ");

    user_command.com = strdup(command);

    if (argument != NULL) {
        user_command.arg = strdup(argument);
    } else {
        user_command.arg = NULL;
    }
    return user_command;
}

struct split_arg split_argument(struct command argument) {
    struct split_arg new_argument = {};

    char *source = strtok(argument.arg, " ");
    char *destination = strtok(NULL, " ");

    if (source != NULL) {
        new_argument.source = source;
    }
    if (destination != NULL) {
        new_argument.destination = destination;
    }
    return new_argument;
}

void exec_command(char *input) {
    const struct command user_command = split_command(input);

    user_command.com[strcspn(user_command.com, "\n")] = '\0';
    if (user_command.arg != NULL)
        user_command.arg[strcspn(user_command.arg, "\n")] = '\0';

    for (int i = 0; i < sizeof(CommandsList) / sizeof(CommandsList[0]); i++) {
        if (strcmp(user_command.com, CommandsList[i].cmd) == 0) {
            CommandsList[i].func(user_command.arg);
            break;
        }
    }
    free(user_command.com);
    free(user_command.arg);
}

// ls command
void list(const char *path) {
    struct dirent *entry;
    if (path == NULL) {
        path = ".";
    }
    DIR *dP = opendir(path);

    // check if the directory got opened successfully
    if (dP == NULL) {
        perror("failed to open directory");
        return;
    }

    // Print the folder|directory name
    while ((entry = readdir(dP)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dP);
}

void remove_dir(const char *path) {
    if (rmdir(path) != 0) {
        perror("failed to delete the directory");
    } else {
        struct dirent *entry;
        // cant be a const because inserting it into the readdir functions causes a warning becasue it expects a non const dir variable
        DIR *dP = opendir(path);

        if (dP == NULL) {
            perror("failed to open the directory to delete the files recursively");
        }

        // ReSharper disable once CppPointerConversionDropsQualifiers
        while ((entry = readdir(dP)) != NULL && (strcmp(entry->d_name, ".") != 0) && (
                   strcmp(entry->d_name, "..") != 0)) {
            if (rmdir(entry->d_name) != 0) {
                perror("failed to delete the directory 02");
            }
        }
        printf("%p", dP);
    }
}

void make_dir(const char *path) {
    if (mkdir(path, 0755) == 0)
        perror("failed to make directory");
}


void remove_file(const char *path) {
    if (remove(path) != 0) {
        perror("failed to delete file");
    }
}

void change_ownership(const char *path) {
    if (chmod(path,S_IRWXU) != 0) {
        perror("failed to get ownership of the file");
    } else {
        printf("file permissions updated successfully");
    }
}

void copy_files(const char *arg) {
    // split the argument into the source and destination
    // make a copy of the source file in the destination file
    int c;
    struct split_arg argument = split_argument((struct command){.arg = (char *)arg});

    FILE *pold_file = fopen(argument.source, "r");
    if (pold_file == NULL) {
        perror("cant open the source file for reading (copy failed) ");
        return;
    }

    FILE *pnew_file = fopen(argument.destination, "w");
    if (pnew_file == NULL) {
        perror("cant open the destination file for reading (copy failed)");
        return;
    }

    while ((c = fgetc(pold_file)) != EOF) {
        fputc(c, pnew_file);
    }
    fclose(pnew_file);
    fclose(pold_file);
}

void move_files(const char *arg) {

    struct split_arg argument = split_argument((struct command){.arg = (char *)arg});

    if (remove(argument.source) != 0) {
        perror("failed while trying to move the file");
    }
    // Create a file
    FILE *pFile = fopen(argument.destination, "w");

    // Close the file
    fclose(pFile);
}

void clear(const char *arg) {
    printf("\033[2J");
    printf("\033[3J");
    printf("\033[H");
}

void echo(const char *arg) {
    printf("%s\n", arg);
}

void exit_(const char *arg) {
    exit(0);
}

void print_cdirectory(const char *arg) {
    char *current_working_directory = getcwd(NULL, 0);
    printf("%s", current_working_directory);
}

void change_directory(const char *path) {
    if (path == NULL) {
        printf("No path found\n");
    } else if (chdir(path) != 0)
        perror("path not found");
}

int main(void) {
    clear("");
    // ReSharper disable once CppDFAEndlessLoop
    while (1) {
        printf("\n$ ");

        char *input = malloc(sizeof(char) * MAX_COMMAND_LENGTH);
        fgets(input, MAX_COMMAND_LENGTH, stdin);
        exec_command(input);
        free(input);
    }
}
