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
        std::cout << "ftok error" << std::endl;
        return 0;
    }

    // 메시지 큐 생성
    msqid = msgget(mykey, IPC_CREAT | 0644);
    if (msqid == -1) {
        std::cout << "msgget error" << std::endl;
        return 0;
    }

    signal(SIGINT, signalHandler);

    std::cout << "wait." << std::endl;
    memset(&msgCalc, 0x00, sizeof(MsgCalc));
    msgrcv(msqid, &msgCalc, sizeof(MsgCalc) - sizeof(long), 1, 0);
    std::cout.flush();

    // 이하는 제대로 받았는지 테스트.
    // 파일에서 아이디랑 비번 일치하는지 확인하도록 수정할 것.
    std::cout << "ID: " << msgCalc.id << std::endl;
    std::cout << "PW: " << msgCalc.pw << std::endl;

    // 존재하는 아이디랑 비밀번호면 1을 전송
    int result = 1; // 0이면 로그인 실패, 1이면 guest, 2이면 관리자
    memset(&msgRslt, 0x00, sizeof(MsgRslt));
    msgRslt.mtype = 2;
    msgRslt.result = result;
    msgsnd(msqid, &msgRslt, sizeof(MsgRslt) - sizeof(long), 0);
    std::cout << "해당 아이디 로그인 승인 완료." << std::endl;
    return 0;
}
