#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>

int main(int argc, char** argv)
{
    int pid;

    // van-e argumentum?
    if (argc < 2) {
        perror("hibas parameter");
        return 1;
    }

    // szám-e az argumentum
    for (int i = 0; argv[1][i] != '\0'; i++) {
        if (!isdigit(argv[1][i])) {
            perror("hibas pid");
            return 1;
        }
    }

    pid = atoi(argv[1]); // char* to int
    kill(pid, SIGALRM);  // signal küldés
    return 0;
}