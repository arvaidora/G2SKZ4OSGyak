/* 	shmctl.c	*/
/*	shmcreate.c-vel keszitett osztott memoria szegmens
        statusanak lekerdezesere, a szegmens megszuntetesere
	alkalmazhato program. 
	IPC_STAT parancs a status lekerdezest,
        IPC_RMID parancs a megszuntetest keri.
 	A statusbol csak a szegmens meretet es annak a processznek
	azonositojat irja ki, amelyik utoljara operalt a szegmensen.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMKEY 123456L

int main()
{
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