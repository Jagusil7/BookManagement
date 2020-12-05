#include <fcntl.h>
#include <iostream>
#include <list>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;
#define MAX_NAME_LEN 64
#define MAX_ID_LEN 20

class Login {
  public:
    Login() {
        memset(this->id, 0x00, MAX_NAME_LEN + 1);
        memset(this->password, 0x00, MAX_NAME_LEN + 1);
        this->personalNo = 0;
    }
    Login(string id, string password) {

        strcpy(this->id, id.c_str());
        strcpy(this->password, password.c_str());
        this->personalNo = 1; // guest 가입하면 자동적으로 1부터
        // personalnumber 부여(따로 넣어줄 필요 X)
    }

    void setId(string id) { memcpy(this->id, id.c_str(), MAX_NAME_LEN); }
    void setPassword(string password) {
        memcpy(this->password, password.c_str(), MAX_NAME_LEN);
    }
    void setPersonalNo(int personalNo) { this->personalNo = personalNo; }

    string getId() { return string(this->id); }
    string getPassword() { return string(this->password); }
    int getPersonalNo() { return this->personalNo; }

  private:
    char id[MAX_ID_LEN];
    char password[MAX_ID_LEN];
    int personalNo;
};

//인자로 로그인 정보가 담겨있는 리스트,찾으려는 아이디와 패스워드가 들어감
//일치하는 아이디와 비밀번호가 있으면 manager:1, guest:2 반환/ 없으면 0 반환
int matchLogin(list<Login> &LoginList, string findid, string findpass) {
    list<Login>::iterator it;
    for (it = LoginList.begin(); it != LoginList.end(); ++it) {
        if (findid == it->getId()) {
            if (findpass == it->getPassword()) {
                if (it->getPersonalNo() == 0) {
                    return 1;
                } else {
                    return 2;
                }
            }
        }
    }
    return 0;
}

struct __MsgCalc {
    long mtype;
    char id[20];
    char pw[20];
    int mode;
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
    // Login class 관련
    list<Login> loginList;
    list<Login>::iterator liter;

    // messageQueue 관련
    int result = 0; // 0이면 실패, 1이면 guest, 2이면 관리자
    MsgCalc msgCalc;
    MsgRslt msgRslt;
    string id;
    string pw;
    int mode; // 가입 0 로그인 1

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

    while (1) {
        int rfd = 0;
        string filepath = "./member.dat";
        Login *rbuf = (Login *)malloc(sizeof(Login));
        rfd = open(filepath.c_str(), O_RDONLY);
        if (rfd == -1) {
            perror("open() error!");
            exit(-1);
        }
        while (read(rfd, rbuf, sizeof(Login)) != 0) {
            Login member(rbuf->getId(), rbuf->getPassword());
            loginList.push_back(member);
        }
        close(rfd);

        for (liter = loginList.begin(); liter != loginList.end(); liter++) {
            if (liter->getId() == "manager123" &&
                liter->getPassword() == "ilovebook")
                liter->setPersonalNo(0);
            cout << liter->getId() << " " << liter->getPassword() << " "
                 << liter->getPersonalNo() << endl;
        }

        cout << "wait..." << std::endl;
        memset(&msgCalc, 0x00, sizeof(MsgCalc));
        msgrcv(msqid, &msgCalc, sizeof(MsgCalc) - sizeof(long), 1, 0);
        cout.flush();

        // 이하는 제대로 받았는지 테스트.
        // 파일에서 아이디랑 비번 일치하는지 확인하도록 수정할 것.
        id = msgCalc.id;
        pw = msgCalc.pw;
        mode = msgCalc.mode;
        if (mode == 0) {
            result = 1;
            Login login(id, pw);

            int tfd;
            string filepath = "./member.dat";
            Login *tbuf = (Login *)malloc(sizeof(Login));
            tfd = open(filepath.c_str(), O_RDWR);
            if (tfd == -1) {
                perror("open() error!");
                exit(-1);
            }
            bool same = false;
            while (read(tfd, tbuf, sizeof(Login)) != 0) {
                if (id == tbuf->getId()) {
                    same = true;
                    close(tfd);
                    break;
                }
            }
            if (same == true) {
                cout << "중복되는 아이디 존재." << endl;
                result = 0;
            } else {
                cout << "가입허가" << endl;
                if (write(tfd, &login, sizeof(Login)) == -1) {
                    perror("write() error");
                    exit(-1);
                }
            }
            close(tfd);

            // 전송
            memset(&msgRslt, 0x00, sizeof(MsgRslt));
            msgRslt.mtype = 2;
            msgRslt.result = result;
            msgsnd(msqid, &msgRslt, sizeof(MsgRslt) - sizeof(long), 0);

        } else if (mode == 1) {
            result = matchLogin(loginList, id, pw);
            if (result != 1 && result != 2) {
                cout << "일치하는 아이디와 비밀번호 없음." << endl;
                result = 0;
            } else {
                cout << "로그인 허가" << endl;
            }
            // 전송
            memset(&msgRslt, 0x00, sizeof(MsgRslt));
            msgRslt.mtype = 2;
            msgRslt.result = result;
            msgsnd(msqid, &msgRslt, sizeof(MsgRslt) - sizeof(long), 0);
        }
    }
    return 0;
}
