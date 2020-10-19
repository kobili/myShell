#include "instructions.h"

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>

// exit the shell
int exec_exit(char** args, int nargs) {
    printf("exiting... \n");
    exit(0);
    return 0;
}

// echo the user's input
int exec_echo(char** args, int nargs) {
    for (int i = 1; i < nargs; i++) {
        if (i == nargs - 1) {
            // print a newline after the last argument
            printf("%s\n", args[i]);
        } else {
            printf("%s ", args[i]);
        }
    }
    return 0;
}

//print the current working directory
int exec_pwd(char** args, int nargs) {

    char* wd = getcwd(NULL, 0);

    if (wd == NULL) {
        perror("pwd");
        free(wd);
        return 1;
    } else {
        printf("%s\n", wd);
        free(wd);
        return 0;
    }

}

// change the current working directory
int exec_cd(char** args, int nargs) {
    int result = chdir(args[1]);

    if (result == -1) {
        perror("cd");
        return 1;
    }

    // print the directory we just changed to
    exec_pwd(args, nargs);
    return 0;
}

// print a list of the current directory's contents
int exec_ls(char** args, int nargs) {
    // open the working directory
    DIR * dirp = opendir(".");

    // handle opendir errors
    if (dirp == NULL) {
        perror("dirp");
        return 1;
    }

    struct dirent * current_entry = readdir(dirp);
    while (current_entry != NULL) {
        printf("%s\n", current_entry->d_name);
        // continue to next entry
        current_entry = readdir(dirp);
    }
    
    // close the directory
    if (closedir(dirp) == -1) {
        perror("closedir");
        return 1;
    }

    return 0;
}

int (* built_in_functions[]) (char**, int) = {
    &exec_exit,
    &exec_echo,
    &exec_pwd,
    &exec_cd,
    &exec_ls
};

char *built_in_commands[] = {
    "exit",
    "echo",
    "pwd",
    "cd",
    "ls"
};

int nbuilt_in_commands = 5;