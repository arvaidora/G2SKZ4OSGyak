#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEMKEY 123456L  /* kulcs a semget-nek; remelem, egyedi */

    int semid,	/* semaphor set azonosito */
        nsems,	/* semaphorok szama a keszletben */
        semnum,	/* semapho szam a set-en belul */
        rtn;	/* visszateresi ertek */

	int semflg;	/* flag */
    int semval;

    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short  *array;
    } arg;
    int cmd;

int main() 
{
    nsems = 1;
    semnum = 1;
    semflg = 00666 | IPC_CREAT;
    semval = 0;
   
    if (semid < 0 ) {perror(" semget hiba"); exit(0);}
	else printf("\n semid: %d ",semid);
    
    //int rtn = semctl(semid, semval, SETVAL, arg);

    semnum = 0;	/* 0-i semaphort azonositom */

    arg.val = 0;
    cmd = SETVAL;	/* allitsd be a semaphor erteket */
	rtn = semctl(semid, semnum, cmd, arg); /* a semid-vel azonositott
					    set 0-ik semaphorat ! */

    printf("\n set  rtn: %d ,semval: %d ",rtn,arg.val);
	printf("\n");

    return 0;
}