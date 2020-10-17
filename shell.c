#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

// exit the shell
void exec_exit(char** args, int nargs) {
    printf("exiting... \n");
    exit(0);
}

// echo the user's input
void exec_echo(char** args, int nargs) {
    for (int i = 1; i < nargs; i++) {
        if (i == nargs - 1) {
            printf("%s\n", args[i]);
        } else {
            printf("%s ", args[i]);
        }
    }
}

void (* built_in_functions[]) (char**, int) = {
    &exec_exit,
    &exec_echo
};

char *built_in_commands[] = {
    "exit",
    "echo"
};

int nbuilt_in_commands = 2;

void execute_instruction(char** args, int nargs) {
    for (int i = 0; i < nbuilt_in_commands; i++) {
        if (strcmp(args[0], built_in_commands[i]) == 0) {
            // execute the command
            return (*built_in_functions[i]) (args, nargs);
        }
    }
}

int main(int argc, char* argv[]) {

    while (1) {
        printf("$ ");

        // read a line from the console and store it in line
        char *line = NULL;
        size_t len = 0;
        ssize_t line_size = getline(&line, &len, stdin);

        // exit if eof
        if (feof(stdin)) {
            exit(0);
        }

        // split the input line by spaces, store the individual strings in args
        // the first string in args is the command; the rest of the strings are arguments
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