#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int exit = 0;

    while (!exit) {
        printf("$ ");

        // read a line from the console and store it in line
        char *line = NULL;
        size_t len = 0;
        ssize_t line_size = getline(&line, &len, stdin);

        // exit if eof
        if (feof(stdin)) {
            exit = 1;
        }

        // split the input line by spaces, store the individual strings in split_input
        // the first string in split_input is the command; the rest of the strings are arguments
        char **split_input = malloc(1024);
        char* token = strtok(line, " \n");
        int ntokens = 0;
        while (token != NULL) {
            split_input[ntokens] = token;
            ntokens++;
            token = strtok(NULL, " \n");
        }

        // execute instruction
        if (strcmp(split_input[0], "exit") == 0) {
            printf("exiting... \n");
            exit = 1;
        }

        // free allocated memory
        free(split_input);
        free(line);
    }


    return 0;
}