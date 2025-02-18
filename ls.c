/*
 * =====================================================================================
 *
 *       Filename:  ls.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/18/2025 15:39:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>


int main(){

    char *path = "folder";
    struct dirent *entry;
    DIR *dP = opendir(path);

    // check if the directory got opened successfully
    if (dP == NULL) {
        perror("opendir");
        return 1;
    }

    // print the folder|directory name
    while ((entry = readdir(dP)) != NULL) {
        char *temporary_variable = entry->d_name;
        printf("%s\n", entry->d_name);
    }
    closedir(dP);

}
