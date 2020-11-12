#include "BookInfo.hpp"
#include <iostream>
#include <string.h>
#include <string>

using namespace std;

Book::Book() {
    memset(this->title, 0x00, MAX_NAME_LEN + 1);
    memset(this->writer, 0x00, MAX_NAME_LEN + 1);
    memset(this->bookNum, 0x00, MAX_NAME_LEN + 1);
    this->status = 0;
}

Book::Book(string title, string writer, string bookNum) {
    memcpy(this->title, title.c_str(), MAX_NAME_LEN);
    memcpy(this->writer, writer.c_str(), MAX_NAME_LEN);
    memcpy(this->bookNum, bookNum.c_str(), MAX_NAME_LEN);
    this->status = 0;
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
void Book::setStatus() {
    if (this->status == 0)
        this->status = 1;
    else if (this->status == 1)
        this->status = 0;
}

string Book::getTitle() { return string(this->title); }
string Book::getWriter() { return string(this->writer); }
string Book::getBookNum() { return string(this->bookNum); }
bool Book::getStatus() { return this->status; }