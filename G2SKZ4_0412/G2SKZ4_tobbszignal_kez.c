#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handleSignal(int signal);

int main ()
{
    signal(SIGINT, handleSignal);
    signal(SIGQUIT, handleSignal);
    while (1) {
        pause();
    }
    return 0;
}

void handleSignal(int sig) {
    switch (sig)
    {
        case SIGINT:
            printf(" Interrupt signal\n");
            signal(SIGINT, SIG_DFL);
            break;
        case SIGQUIT:
            printf(" Quit signal\n");
            break;
        default:
            break;
    }
}