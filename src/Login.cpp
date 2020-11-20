#include "Login.hpp"
#include <iostream>
#include <string.h>
#include <string>

using namespace std;

Login::Login() {
    memset(this->id, 0x00, MAX_NAME_LEN + 1);
    memset(this->password, 0x00, MAX_NAME_LEN + 1);
    this->personalNo = 0;
}

Login::Login(
    string id,
    string password) { // Only guest can register, (manager: id-manager123,
                       // password-ilovebook, personalNum-0 )
    memcpy(this->id, id.c_str(), MAX_NAME_LEN);
    memcpy(this->password, password.c_str(), MAX_NAME_LEN);
    this->personalNo = ++number;
}

void Login::setId(string id) { memcpy(this->id, id.c_str(), MAX_NAME_LEN); }
void Login::setPassword(string password) {
    memcpy(this->password, password.c_str(), MAX_NAME_LEN);
}
void Login::setPersonalNo() {}

string Login::getId() { return string(this->id); }
string Login::getPassword() { return string(this->writer); }
int Login::getPersonalNo() { return this->status; }
