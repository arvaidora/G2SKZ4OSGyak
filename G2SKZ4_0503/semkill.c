#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define SEMKEY 123456L  /* kulcs a semget-nek; remelem, egyedi */


	int semid,nsems,rtn;
	int semflg;
	int cmd;

    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short  *array;
    } arg;

int main()
{
	nsems = 1;
	semflg = 00666 | IPC_CREAT;
	semid = semget (SEMKEY, nsems, semflg);
	if (semid < 0 ) {perror(" semget hiba"); exit(0);}
	else printf("\n semid: %d ",semid);
	printf ("\n");

	cmd = IPC_RMID;		/* Ez a megszuntetes parancsa */
	rtn = semctl(semid,0, cmd, arg);

	printf("\n kill rtn: %d ",rtn);
	printf("\n");

}