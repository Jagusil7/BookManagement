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

void signalHandler(int signum) {
    if (signum == SIGINT) {
        msgctl(msqid, IPC_RMID, NULL);
    }
}

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

    signal(SIGINT, signalHandler); // 뭔데

    puts("wait.");
    memset(&msgCalc, 0x00, sizeof(MsgCalc));
    msgrcv(msqid, &msgCalc, sizeof(MsgCalc) - sizeof(long), 1, 0);
    printf("ID: %d\n", msgCalc.data);

    fflush(stdout);
    return 0;
}
