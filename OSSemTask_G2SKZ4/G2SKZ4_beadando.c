/*L9. Irjon C nyelvu programot, ami
letrehoz ket csovezeteket (ket file deszkriptor part)
elforkol
a szulo elkuldi a sajat pidjet a gyerkmeknek az egyik csovon
a gyermek kiirja a kepernyore es visszakuldi egy az ovet a masik csovon
megszunnek a processzek (a szulo megvarja a gyereket)*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main() {
    // file descriptorok
    int fd1[2]; // ebbe ír a szülő
    int fd2[2]; // ebbe ír a gyerek

    int pid = 0; // a pid értékének tárolására
    int child;   // a fork() hívás eredményének tárolására

    // csővezetékek létrehozása
    // hiba esetén kilép
    if (pipe(fd1) || pipe(fd2)) {
        perror("Hiba a pipe letrehozasakor");
        return 1;
    }

    // Gyerek processz létrehozása a fork() paranccsal
    if ((child = fork()) != 0) {
        // itt a szülő processzben vagyunk

        // pid lekérése
        pid = getpid();

        // lezárom a nem használt deszkriptorokat
        close(fd1[0]); // szülő READ
        close(fd2[1]); // gyerek WRITE

        printf("Szulo pid kuldese a gyereknek: %d\n", pid);
        // elküldöm a pid-et a gyerek processznek
        write(fd1[1], &pid, sizeof(pid));
        // lezárom a szülő WRITE deszkriptorát
        close(fd1[1]);

        // beolvasom a pid-et a csővezetékről
        read(fd2[0], &pid, sizeof(pid));
        // kiírom
        printf("A kapott pid: %d\n", pid);
        // lezárom a gyerek READ deszkriptorát
        close(fd2[1]);

        // gyerek processz megvárása
        wait(&child);
    }
    else if (child == 0) {
        // itt a gyerek processzben vagyunk

        // lezárom a nem használt deszkriptorokat
        close(fd1[1]); // szülő WRITE
        close(fd2[0]); // gyerek READ

        // beolvasom a pid-et a csővezetékről
        read(fd1[0], &pid, sizeof(pid));
        // kiírom
        printf("-A kapott pid: %d\n", pid);
        // lezárom a szülő READ deszkriptorát
        close(fd1[0]);

        // pid lekérése
        pid = getpid();
        
        printf("-Gyerek pid kuldese a szulonek %d\n", pid);
        // elküldöm a pid-et a szülő processznek
        write(fd2[1], &pid, sizeof(pid));
        // lezárom a gyerek WRITE deszkriptorát
        close(fd2[1]);
    }

    return 0;
}