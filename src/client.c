#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

struct __MsgCalc {
    long mtype;
    int data;
};
typedef struct __MsgCalc MsgCalc;

struct __MsgRslt {
    long mtype;
    int result;
};
typedef struct __MsgRslt MsgRslt;

key_t mykey = 0;
int msqid = 0;

int main(void) {
    MsgCalc msgCalc;
    MsgRslt msgRslt;

    // 키생성 (path, 같은 경로에 대한 구분자)
    mykey = ftok("mykey", 1);
    if (mykey == -1) {
        printf("ftok error");
        return 0;
    }

    // 메시지 큐 생성
    msqid = msgget(mykey, IPC_CREAT | 0644);
    if (msqid == -1) {
        printf("msgget error");
        return 0;
    }

    printf("enter your ID: ");
    fflush(stdout);
    int data;
    scanf("%d", &data);
    fflush(stdin);

    memset(&msgCalc, 0x00, sizeof(MsgCalc));
    msgCalc.mtype = 1;
    msgCalc.data = data;
    msgsnd(msqid, &msgCalc, sizeof(MsgCalc) - sizeof(long), 0);
    return 0;
}
