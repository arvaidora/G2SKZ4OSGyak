#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int pid;
    int status;

    if ((pid = fork()) < 0)
        perror("fork hiba");
    else if (pid == 0) /* gyermek */
        if (execl("./child", "child", (char *)NULL) < 0)
            perror("execl error");
    if (wait(&status) != pid)
        perror("wait hiba"); /*szülő */

    return 0;
}