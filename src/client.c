#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

struct __MsgCalc {
    long mtype;
    char id[20];
    char pw[20];
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

    char id[20];
    char pw[20];

    printf("enter your ID: ");
    fflush(stdout);
    scanf("%s", id);
    fflush(stdin);

    printf("enter your PW: ");
    fflush(stdout);
    scanf("%s", pw);

    memset(&msgCalc, 0x00, sizeof(MsgCalc));
    msgCalc.mtype = 1;
    strcpy(msgCalc.id, id);
    strcpy(msgCalc.pw, pw);
    msgsnd(msqid, &msgCalc, sizeof(MsgCalc) - sizeof(long), 0);

    memset(&msgRslt, 0x00, sizeof(MsgRslt));
    msgrcv(msqid, &msgRslt, sizeof(MsgRslt) - sizeof(long), 2, 0);
    if (msgRslt.result == 1) {
        printf("로그인성공!");
    } else {
        printf("로그인 실패");
        printf("%d", msgRslt.result);
    }
    return 0;
}
