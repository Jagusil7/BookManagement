#ifndef __BOOKINFO_M__
#define __BOOKINFO_H__

#include <iostream>
#include <string>

using namespace std;

#define MAX_NAME_LEN 32

class Book {
  public:
    Book();
    Book(string title, string writer, string bookNum);

    void setTitle(string title);
    void setWriter(string writer);
    void setBookNum(string bookNum);
    void setStatus();

    string getTitle();
    string getWriter();
    string getBookNum();
    bool getStatus();

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


    Book* next = nullptr;
  private:
    char title[MAX_NAME_LEN];
    char writer[MAX_NAME_LEN];
    char bookNum[MAX_NAME_LEN];
    bool status;
   
};
#endif
