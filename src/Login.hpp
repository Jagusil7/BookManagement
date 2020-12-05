#ifndef __LOGIN_M__
#define __LOGIN_H__

#include <iostream>
#include <string.h>
#include <string>

using namespace std;
#define MAX_NAME_LEN 64
#define MAX_ID_LEN 20

// server만 쓰임
class Login {
  public:
    Login();
    Login(string id, string password);

    void setId(string id);
    void setPassword(string password);
    void setPersonalNo(int personalNo) { this->personalNo = personalNo; }

    string getId() { return string(this->id); }
    string getPassword() { return string(this->password); }
    int getPersonalNo() { return this->personalNo; }

  private:
    char id[MAX_ID_LEN];
    char password[MAX_ID_LEN];
    int personalNo;
};

#endif
