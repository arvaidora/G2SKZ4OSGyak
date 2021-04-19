#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    int child;
    char * myfifo = "g2skz4";
    
    mkfifo(myfifo, S_IRUSR | S_IWUSR);

    child = fork();

    if (child > 0) {
        char s[1024];
        int fd = open(myfifo, O_RDONLY);
        read(fd, s, sizeof(s));
        close(fd);
        printf("%s", s);
        unlink(myfifo);
    }
    else if (child == 0) {
        int fd = open(myfifo, O_WRONLY);
        write(fd, "Arvai Dora\n", 11);
        close(fd);
    }

    return 0;
}
