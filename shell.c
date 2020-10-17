#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

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

// these functions return 0 when successfully executed
// returns 1 on error
int (* built_in_functions[]) (char**, int) = {
    &exec_exit,
    &exec_echo,
    &exec_pwd
};

char *built_in_commands[] = {
    "exit",
    "echo",
    "pwd"
};

int nbuilt_in_commands = 3;

// execute the instruction corresponding to args[0]
// args[0] is the actual command itself - the rest of args is arguments to the instruction
// returns 0 upon successful execution, 1 otherwise
int execute_instruction(char** args, int nargs) {
    for (int i = 0; i < nbuilt_in_commands; i++) {
        if (strcmp(args[0], built_in_commands[i]) == 0) {
            // execute the command
            return (*built_in_functions[i]) (args, nargs);
        }
    }
    return 1;
}

int main(int argc, char* argv[]) {

    while (1) {
        printf("$ ");

        // read a line from the console and store it in line
        char *line = NULL;
        size_t len = 0;
        ssize_t line_size = getline(&line, &len, stdin);

        // if the user inputs an empty line, ignore it and start the next prompt
        if (line_size == 1) {
            continue;
        }

        // exit if eof
        if (feof(stdin)) {
            exit(0);
        }

        // split the input line by spaces, store the individual strings in args
        char **args = malloc(1024);
        char* token = strtok(line, " \n");
        int ntokens = 0;
        while (token != NULL) {
            args[ntokens] = token;
            ntokens++;
            token = strtok(NULL, " \n");
        }

        execute_instruction(args, ntokens);

        // free allocated memory
        free(args);
        free(line);
    }


    return 0;
}