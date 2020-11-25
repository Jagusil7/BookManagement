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

    signal(SIGINT, signalHandler);

    puts("wait.");
    memset(&msgCalc, 0x00, sizeof(MsgCalc));
    msgrcv(msqid, &msgCalc, sizeof(MsgCalc) - sizeof(long), 1, 0);
    fflush(stdout);

    // 이하는 제대로 받았는지 테스트.
    // 파일에서 아이디랑 비번 일치하는지 확인하도록 수정할 것.
    printf("ID: %s\n", msgCalc.id);
    printf("PW: %s\n", msgCalc.pw);

    // 존재하는 아이디랑 비밀번호면 1을 전송
    int result = 1;
    memset(&msgRslt, 0x00, sizeof(MsgRslt));
    msgRslt.mtype = 2;
    msgRslt.result = result;
    msgsnd(msqid, &msgRslt, sizeof(MsgRslt) - sizeof(long), 0);
    printf("해당 아이디 로그인 승인 완료.");
    return 0;
}
