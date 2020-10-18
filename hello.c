#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {

    int n;
    for (int i = 0; i < argc; i++) {
        n = atoi(argv[i]);
        printf("%d\n", n);
    }

    return 0;
}