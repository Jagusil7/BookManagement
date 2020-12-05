#ifndef __BOOKINFO_M__
#define __BOOKINFO_H__

#include <iostream>
#include <string.h>
#include <string>

using namespace std;
#define MAX_NAME_LEN 64

class Book {
  public:
    Book();
    Book(string title, string writer, string bookNum, string id = "");
    void setTitle(string title);
    void setWriter(string writer);
    void setBookNum(string bookNum);
    // void setStatus(string want) {
    //    this->status = want; } // want = id?
    /*void setStatus(string want) {
        memcpy(this->status, want.c_str(), MAX_NAME_LEN);
    }*/
    void setStatus(string status);

    string getTitle() { return string(this->title); }
    string getWriter() { return string(this->writer); }
    string getBookNum() { return string(this->bookNum); }
    string getStatus() { return string(this->status); }

    // Resgister book
    void bookRegi();
    // Delete book
    void bookDel();
    // Print list
    void printList();
    // Rent book
    void bookRent();
    // Return book
    void bookReturn();
    // Search book by title or writer
    void bookSearch();

    Book *next = NULL;

  private:
    char title[MAX_NAME_LEN];
    char writer[MAX_NAME_LEN];
    char bookNum[MAX_NAME_LEN];
    char status[MAX_NAME_LEN];
};

#endif
