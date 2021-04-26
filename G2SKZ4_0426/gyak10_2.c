#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MSGKEY 654321L

struct msgbuf1 {		
	long mtype;
	char mtext[512];
} msgbuf, *msgp;		/* message buffer es pointere */

struct msqid_ds ds, *buf;	/* uzenetsorhoz asszocialt struktura
					 es pointere*/

int main() {
    int child = 0;

    int msgid;
    key_t key = MSGKEY;
    int msgflg;
    int rtn, msgsz;

    if ((child = fork()) == 0) {
        msgflg = 00666 | IPC_CREAT;
        msgid = msgget(key, msgflg);
        if (msgid == -1) {
            perror("\n The msgget system call failed!");
            return -1;
        }
        msgp = &msgbuf;
        msgp->mtype = 1; // text
        
        strcpy(msgp->mtext, "uzenet");
        msgsz = strlen(msgp->mtext) + 1;
        rtn = msgsnd(msgid, (struct msguf *) msgp, msgsz, msgflg);

        return 0;

    }
    else {
        int mtype;

        msgflg = 00666 | IPC_CREAT | MSG_NOERROR;
        msgid = msgget(key, msgflg);
        if (msgid == -1) {
            perror("\n The msgget system call failed!");
            return -1;
        }

        msgp = &msgbuf;
        buf = &ds;
        msgsz = 20;
        mtype = 0;

        rtn = msgctl(msgid, IPC_STAT, buf);
        printf("\n Az uzenetek szama: %d\n",buf->msg_qnum);

        if (buf->msg_qnum) {		/* van-e uzenet?*/
		/* veszem a kovetkezo uzenetet: */
            rtn = msgrcv(msgid,(struct msgbuf *)msgp, msgsz, mtype, msgflg);
            printf("\n Az rtn: %d,  a vett uzenet:%s\n",rtn, msgp->mtext);
            rtn = msgctl(msgid,IPC_STAT,buf); /* uzenetsor adatokat lekerdezem,
                        benne azt is, hany uzenet van meg */
        }
        return 0;
    }
}