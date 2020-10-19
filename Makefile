shell: shell.c instructions.c
	gcc -o shell shell.c instructions.c

test: hello.c
	gcc -o test hello.c