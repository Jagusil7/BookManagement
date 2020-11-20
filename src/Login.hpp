#ifndef __LOGIN_M__
#define __LOGIN_H__

#include <iostream>
#include <string>

using namespace std;

#define MAX_NAME_LEN 10

class Login {
  public:
    Login();
    Login(string id, string password);

    void setId(string id);
    void setPassword(string password);
    void setPersonalNo(int personalNo);

    string getId();
    string getPassword();
    string getPersonalNo();

    static int number;

  private:
    char id[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];
    int personalNo;
};
#endif
