#include <stdio.h>
#include <unistd.h>

int main() {
    int fd[2];
    int child;

    if (pipe(fd)) {
        perror("error");
        return 1;
    }

    child = fork();

    if (child > 0) {
        char s[1024];
        close(fd[1]);
        read(fd[0], s, sizeof(s));
        printf("%s", s);
    }
    else if (child == 0) {
        close(fd[0]);
        write(fd[1], "AD G2SKZ4\n", 10);
        close(fd[1]);
    }
}