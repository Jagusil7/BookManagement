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

int main(void) {
    key_t mykey = ftok("mykey", 1); // 서버랑 같은 키 써야 함 주의.
    int msquid = msgget(mykey, IPC_CREAT);

    int x = 0;
    int y = 0;
    char op = 0;

    MsgCalc msgCalc;
    MsgRslt msgRslt;

    puts("Input: [x] [op] [y]");
    while (1) {
        printf("<<");
        scanf("%d %c %d", &x, &op, &y);
        fflush(stdout);
        fflush(stdin);
        memset(&msgCalc, 0x00, sizeof(MsgCalc));
        msgCalc.mtype = MSG_TYPE_CALC;
        msgCalc.calc.x = x;
        msgCalc.calc.y = y;
        msgCalc.calc.op = op;
        msgsnd(msqid, &msgCalc, MSG_SIZE_CALC, 0);

        memset(&msgRslt, 0x00, sizeof(MsgRslt));
        msgrcv(msqid, &msgRslt, MSG_SIZE_RSLT, MSG_TYPE_RSLT, 0);
        printf(">> %d\n", msgRslt.rslt);
    }
    return 0;
}
