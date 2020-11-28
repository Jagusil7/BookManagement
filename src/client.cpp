#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <iostream>

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
        std::cout << "ftok error" << std::endl;
        return 0;
    }

    // 메시지 큐 생성
    msqid = msgget(mykey, IPC_CREAT | 0644);
    if (msqid == -1) {
        std::cout << "msgget error" << std::endl;
        return 0;
    }

    char id[20];
    char pw[20];

    std::cout << "enter your ID: ";
    std::cout.flush();
    std::cin >> id;

    std::cout << "enter your PW: ";
    std::cout.flush();
    std::cin >> pw;

    memset(&msgCalc, 0x00, sizeof(MsgCalc));
    msgCalc.mtype = 1;
    strcpy(msgCalc.id, id);
    strcpy(msgCalc.pw, pw);
    msgsnd(msqid, &msgCalc, sizeof(MsgCalc) - sizeof(long), 0);

    memset(&msgRslt, 0x00, sizeof(MsgRslt));
    msgrcv(msqid, &msgRslt, sizeof(MsgRslt) - sizeof(long), 2, 0);
    if (msgRslt.result == 1) {
        std::cout << "로그인 성공!";
    } else {
        std::cout << "로그인 실패 " << msgRslt.result;
    }
    return 0;
}
