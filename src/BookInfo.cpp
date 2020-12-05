#include "BookInfo.hpp"
#include <iostream>
#include <string.h>
#include <string>

using namespace std;
#define MAX_NAME_LEN 64

Book::Book() {
    memset(this->title, 0x00, MAX_NAME_LEN + 1);
    memset(this->writer, 0x00, MAX_NAME_LEN + 1);
    memset(this->bookNum, 0x00, MAX_NAME_LEN + 1);
    memset(this->status, 0x00, MAX_NAME_LEN + 1);
}
Book::Book(string title, string writer, string bookNum, string id) {
    memcpy(this->title, title.c_str(), MAX_NAME_LEN);
    memcpy(this->writer, writer.c_str(), MAX_NAME_LEN);
    memcpy(this->bookNum, bookNum.c_str(), MAX_NAME_LEN);
    memcpy(this->status, id.c_str(), MAX_NAME_LEN);
}
void Book::setTitle(string title) {
    memcpy(this->title, title.c_str(), MAX_NAME_LEN);
}
void Book::setWriter(string writer) {
    memcpy(this->writer, writer.c_str(), MAX_NAME_LEN);
}
void Book::setBookNum(string bookNum) {
    memcpy(this->bookNum, bookNum.c_str(), MAX_NAME_LEN);
}
void Book::setStatus(string status) {
    memcpy(this->status, status.c_str(), MAX_NAME_LEN);
}
