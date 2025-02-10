/*
 * =====================================================================================
 *
 *       Filename:  current_directory.c
 * 
 *
 *        Version:  1.0
 *        Created:  02/10/2025 10:26:51 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <stdio.h>
#include <linux/limits.h>

int main()
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s", cwd);
    else {
        perror("getcwd() error");
        return 1;
    }
    return 0;
}





