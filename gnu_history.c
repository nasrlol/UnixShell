/*
 * =====================================================================================
 *
 *       Filename:  gnu_history.c
 *
 *    Description: testing GNU HISTORY AND GNU READLINE 
 *
 *        Version:  1.0
 *        Created:  02/05/2025 19:31:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main() {
    char *input;

    using_history();  // Initialize history

    while (1) {
        input = readline("shell> ");  // Read user input

        if (!input) break;  // Handle Ctrl+D (EOF)

        if (*input) {  // If input is not empty
            add_history(input);  // Save input to history
        }

        printf("You typed: %s\n", input);

        free(input);  // readline() allocates memory, so free it
    }

    return 0;
}
