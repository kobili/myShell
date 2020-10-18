#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

// these functions return 0 when successfully executed
// returns 1 on error

// exit the shell
int exec_exit(char** args, int nargs);

// echo the user's input
int exec_echo(char** args, int nargs);

//print the current working directory
int exec_pwd(char** args, int nargs);

// change the current working directory
int exec_cd(char** args, int nargs);


extern int (* built_in_functions[]) (char**, int);
extern char* built_in_commands[];
extern int nbuilt_in_commands;


#endif