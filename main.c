#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <readline/history.h>
#include <readline/readline.h>

int main() {
    const bool RUNNING = true;
    char *COMMAND_HISTORY;
    COMMAND_HISTORY = (char *)malloc(sizeof(char));


    // RUNNING THE PROGRAM ON AN ENDLESS LOOP
    // BREAKS WHEN USER ENTERS EXIT
    while(RUNNING) {
        char *TEMP = "";

        scanf("%s", &TEMP);
        for (int i = 0; i != "/0"; i++)
        {
                tolower(TEMP[0]);
        }

        if (TEMP == "exit") {
            RUNNING = false;
            printf("exited successfully");
        }
        else {
            strcpy(&TEMP, (COMMAND_HISTORY));
            printf("%s",COMMAND_HISTORY);
        }

    }
    return 0;
}
