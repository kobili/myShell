#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "instructions.h"


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
    printf("command not found '%s'\n", args[0]);
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