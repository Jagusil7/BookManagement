// 서버-클라이언트 공통부분: 시작
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define MSG_TYPE_CALC 1
#define MSG_TYPE_RSLT 2
#define MSG_SIZE_CALC (sizeof(MsgCalc) - sizeof(long))
#define MSG_SIZE_RSLT (sizeof(MsgRslt) - sizeof(long))

struct __Calc {
    int x;
    int y;
    char op;
};
typedef struct __Calc Calc;

struct __MsgCalc {
    long mtype;
    struct __Calc calc;
};
typedef struct __MsgCalc MsgCalc;

struct __MsgRslt {
    long mtype;
    int rslt;
};
typedef struct __MsgRslt MsgRslt;

key_t mykey = 0;
int msqid = 0;
// 서버-클라이언트 공통부분: 끝

void signalHandler(int signum) {
    if (signum == SIGINT) {
        msgctl(msqid, IPC_RMID, NULL);
        exit(0);
    }
}
int calculate(Calc calc) {
    switch (calc.op) {
    case '+':
        return calc.x + calc.y;
    case '-':
        return calc.x - calc.y;
    case '*':
        return calc.x * calc.y;
    case '/':
        return calc.x / calc.y;
    default:
        return 0;
    }
}

int main(int argc, char const *argv[]) {
    MsgCalc msgCalc;
    MsgRslt msgRslt;
    mykey = ftok("mykey", 1);
    msqid = msgget(mykey, IPC_CREAT | 0644);
    signal(SIGINT, signalHandler);
    while (1) {
        puts("Wait");
        memset(&msgCalc, 0x00, sizeof(MsgCalc));                  // 초기화
        msgrcv(msqid, &msgCalc, MSG_SIZE_CALC, MSG_TYPE_CALC, 0); // 받기
        printf("Receive: %d %c %d\n", msgCalc.calc.x, msgCalc.calc.op,
               msgCalc.calc.y);

        memset(&msgRslt, 0x00, sizeof(MsgRslt));

        msgRslt.mtype = MSG_TYPE_RSLT;
        msgRslt.rslt = calculate(msgCalc.calc);
        msgsnd(msqid, &msgRslt, MSG_SIZE_RSLT, 0);
        printf("Send: %d\n", msgRslt.rslt);
        fflush(stdout);
    }
    return 0;
}
