#include "Login.hpp"
#include <iostream>
#include <string.h>
#include <string>

using namespace std;
#define MAX_NAME_LEN 64
#define MAX_ID_LEN 20

Login::Login() {
    memset(this->id, 0x00, MAX_NAME_LEN + 1);
    memset(this->password, 0x00, MAX_NAME_LEN + 1);
    this->personalNo = 0;
}
Login::Login(string id, string password) {
    strcpy(this->id, id.c_str());
    strcpy(this->password, password.c_str());
    this->personalNo = 1; // guest 가입하면 자동적으로 1부터
    // personalnumber 부여(따로 넣어줄 필요 X)
}
void Login::setId(string id) { memcpy(this->id, id.c_str(), MAX_NAME_LEN); }
void Login::setPassword(string password) {
    memcpy(this->password, password.c_str(), MAX_NAME_LEN);
}
