#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void signal_kezel();

int main() {
    int pid = getpid(); // saját pid lekérése
    printf("pid: %d\n", pid);  // pid kiíratása
    printf("varakozas...\n");
    signal(SIGALRM, signal_kezel); // signálra várakozás 
    pause();
    printf("kesz\n");
}

void signal_kezel() {
    printf("G2SKZ4\n");
}