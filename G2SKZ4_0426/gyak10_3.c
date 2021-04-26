#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMKEY 123456L

int main() {
    int child = 0;

    if ((child = fork()) == 0) {
        int shmid;		/* osztott mem azonosito */
        key_t key;		/* kulcs a shmem-hez */
        int size=512;		/* osztott szegmens meret */
        int shmflg;		/* flag a jellemzokhoz */

        key = SHMKEY;
        /* Megnezzuk, van SHMKEY-es,size meretu szegmens. */
        shmflg = 0;
        if ((shmid=shmget( key, size, shmflg)) < 0) {
            printf("\n Nincs meg szegmens! Keszitsuk el!");
            shmflg = 00666 | IPC_CREAT;
            if ((shmid=shmget( key, size, shmflg)) < 0) {
                perror("\n Az shmget system-call sikertelen!");
                exit(-1);
            }
        } else printf("\n Van mar szegmens!");

        printf("  Az shmid azonositoja %d: \n", shmid);

        exit (0);
    }
    else {
        if (child = fork() == 0) {
            int shmid;		/* osztott mem azonosito */
            key_t key;		/* kulcs a shmem-hez */
            int size=512;		/* osztott szegmens meret */
            int shmflg;		/* flag a jellemzokhoz */
            struct vmi {
                int  hossz;
                char szoveg[512-sizeof(int)];
            } *segm;		/* Ezt a strukturat kepezzuk a szegmensre */
            
            key = SHMKEY;
            shmflg = 0;	/* Nincs IPC_CREAT, feltetelezzuk, az shmcreate
                        keszitett osztott memoria szegmenst */
            if ((shmid=shmget( key, size, shmflg)) < 0) {
                perror("\n Az shmget system-call sikertelen!");
                exit(-1);
            }

            /* Attach */
            shmflg = 00666 | SHM_RND;
            segm = (struct vmi *)shmat(shmid, NULL, shmflg); /* Itt a NULL azt
                        jelenti, hogy az OS-re bizom, milyen
                        cimtartomanyt hasznaljon. */
            if (segm == (void *)-1) {
                perror(" Sikertelen attach");
                exit (-1);
            }

            /* Sikeres attach utan a segm cimen ott az osztott memoria.
            Ha van benne valami, kiiratom, utana billentyuzetrol kerek
            uj beteendo szoveget */

            if (strlen(segm->szoveg) > 0) 
                printf("\n Regi szoveg: %s (%d hosszon)",segm->szoveg,segm->hossz);
        
            printf("\n Uj szoveget kerek!\n");
            gets(segm->szoveg);
            printf("\n Az uj szoveg: %s\n",segm->szoveg);
            segm->hossz=strlen(segm->szoveg);
                
            /* Detach */
            shmdt(segm);

            exit(0);
        }
        else {
            int shmid;		/* osztott mem azonosito */
            key_t key;		/* kulcs a shmem-hez */
            int size=512;		/* osztott szegmens meret */
            int shmflg;		/* flag a jellemzokhoz */
            int rtn;		/* rensz.hivas visszter. ertek */
            int cmd;		/* parancskod */
            struct shmid_ds shmid_ds, *buf; /* adatstruktura a status
                            adatok fogadasahoz */
            buf = &shmid_ds;	/* es annak pointere */

            key = SHMKEY;
            shmflg = 0;	/* Nincs IPC_CREAT, feltetelezzuk, az shmcreate
                        keszitett osztott memoria szegmenst */
            if ((shmid=shmget( key, size, shmflg)) < 0) {
                perror("\n Az shmget system-call sikertelen!");
                exit(-1);
            }

        /* Get the command */
        do {
            printf("\n Add meg a parancs szamat ");
            printf("\n 0 IPC_STAT (status) ");
            printf("\n 1 IPC_RMID (torles)   >  ");
            scanf("%d",&cmd);
            } while (cmd < 0 && cmd > 1);

            switch (cmd)
            {
            case 0: rtn = shmctl(shmid, IPC_STAT, buf);
                printf("\n  Segm. meret: %d",buf->shm_segsz);
                printf("\n  Utolso shmop-os proc. pid: %d\n ",buf->shm_lpid);
                break;
            case 1: rtn = shmctl(shmid, IPC_RMID, NULL);
                printf("\n Szegmens torolve\n");
            }
            
            exit(0);
        }
    }
}