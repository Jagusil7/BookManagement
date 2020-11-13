#include <fcntl.h>
#include <iostream>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <string.h>
#include <string>

using namespace std;
#define MAX_NAME_LEN 32

// 디버그 편의를 위해 단일 파일로 제작.
// 추후 완전히 완성 후 분리.

class Book {
  public:
    Book() {
        memset(this->title, 0x00, MAX_NAME_LEN + 1);
        memset(this->writer, 0x00, MAX_NAME_LEN + 1);
        memset(this->bookNum, 0x00, MAX_NAME_LEN + 1);
        this->status = 0;
    }
    Book(string title, string writer, string bookNum) {
        memcpy(this->title, title.c_str(), MAX_NAME_LEN);
        memcpy(this->writer, writer.c_str(), MAX_NAME_LEN);
        memcpy(this->bookNum, bookNum.c_str(), MAX_NAME_LEN);
        this->status = 0;
    }

    void setTitle(string title) {
        memcpy(this->title, title.c_str(), MAX_NAME_LEN);
    }
    void setWriter(string writer) {
        memcpy(this->writer, writer.c_str(), MAX_NAME_LEN);
    }
    void setBookNum(string bookNum) {
        memcpy(this->bookNum, bookNum.c_str(), MAX_NAME_LEN);
    }
    void setPublishing(int pub) { this->publishing = pub; }
    void setStatus(int want) { this->status = want; }

    string getTitle() { return string(this->title); }
    string getWriter() { return string(this->writer); }
    string getBookNum() { return string(this->bookNum); }
    int getStatus() { return this->status; }
    int getPublishing() { return this->publishing; }

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

    Book *next = nullptr;

  private:
    char title[MAX_NAME_LEN];
    char writer[MAX_NAME_LEN];
    char bookNum[MAX_NAME_LEN];
    int status;
    int publishing;
};

// 모드에 따라 이름/저자로 완전히 일치하는 도서 찾기
// moode: 0(제목), 기타(저자)
list<Book>::iterator find_same(list<Book> &myList, int mode, string compare) {
    list<Book>::iterator it;
    string temp;
    for (it = myList.begin(); it != myList.end(); ++it) {
        if (mode == 0)
            temp = (*it).getTitle();
        else
            temp = (*it).getWriter();
        if (temp == compare) {
            return it;
        }
    }
    return myList.end();
    // C++에서 iterator는 null을 가질 수 없어서 이렇게 반환.
}
// 해당 문자열이 포함된 도서 찾기. mode는 동일.
list<Book>::iterator find_contain(list<Book> &myList, int mode,
                                  string compare) {
    list<Book>::iterator it;
    string temp;
    for (it = myList.begin(); it != myList.end(); ++it) {
        if (mode == 0)
            temp = (*it).getTitle();
        else
            temp = (*it).getWriter();
        if (temp.find(compare) != string::npos) {
            return it;
        }
    }
    return myList.end();
}

int main() {
    int fd = 0;
    string filename = "./BookList.dat";

    list<Book> bookList;
    list<Book>::iterator iter;

    fd = open(filename.c_str(), O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
        cout << "open() error!" << endl;
        exit(-1);
    }
    Book *buf = new Book();
    while (read(fd, buf, sizeof(Book)) != 0) {
        Book book(buf->getTitle(), buf->getWriter(), buf->getBookNum());
        bookList.push_back(book);
    }

    while (1) {
        cout << "<MENU>" << endl
             << "[0] Add Book" << endl
             << "[1] Delete Book" << endl
             << "[2] Print List" << endl
             << "[3] Search" << endl
             << "[4] Save and Exit" << endl
             << ">>";
        int menu;
        cin >> menu;
        cout << endl;
        if (menu == 0) { // add book
            string title = "";
            string writer = "";
            string bookN = "";

            cout << "[ADD]" << endl << "Title: ";
            cin >> title;
            cout << "Writer: ";
            cin >> writer;
            cout << "BookNo.: ";
            cin >> bookN;

            Book book(title, writer, bookN);
            bookList.push_back(book);

        } else if (menu == 1) { // delete book
            string del;
            cout << "[DELETE]" << endl << "Title: ";
            cin >> del;
            for (iter = bookList.begin(); iter != bookList.end(); iter++) {
                if (iter->getTitle() == del) {
                    bookList.erase(iter);
                    break;
                }
            }
            if (iter == bookList.end()) {
                cout << "ERROR: doesn't exist";
            }
        } else if (menu == 2) { // print list
            cout << "[PRINT]" << endl;
            for (iter = bookList.begin(); iter != bookList.end(); ++iter) {
                cout << "TITLE:" << iter->getTitle()
                     << " WRITER:" << iter->getWriter()
                     << " BOOKNUM:" << iter->getBookNum()
                     << " STATUS:" << iter->getStatus() << endl;
            }
        } else if (menu == 3) {
            cout << "[SEARCH]" << endl;
            cout << "Find Title: ";
            string title;
            cin >> title;
            iter = find_same(bookList, 0, title);
            if (iter == bookList.end()) {
                iter = find_contain(bookList, 0, title);
                if (iter == bookList.end())
                    cout << "찾는 도서가 없음." << endl;
                else
                    cout << "해당 문자열이 들어간 도서 존재." << endl
                         << "TITLE:" << iter->getTitle()
                         << " WRITER:" << iter->getWriter()
                         << " BOOKNUM:" << iter->getBookNum()
                         << " STATUS:" << iter->getStatus() << endl;
            } else
                cout << "도서 존재." << endl
                     << "TITLE:" << iter->getTitle()
                     << " WRITER:" << iter->getWriter()
                     << " BOOKNUM:" << iter->getBookNum()
                     << " STATUS:" << iter->getStatus() << endl;

        } else if (menu == 4) { // save doc and exit
            if (remove(filename.c_str()) == -1) {
                perror("remove() error!");
                exit(-1);
            }
            fd = open(filename.c_str(), O_CREAT | O_RDWR, 0644);
            if (fd == -1) {
                perror("init() error!");
                exit(-1);
            }
            ssize_t wsize = 0;
            for (iter = bookList.begin(); iter != bookList.end(); iter++) {
                wsize = write(fd, &(*iter), sizeof(Book));
                if (wsize == -1) {
                    cout << "write() error!" << endl;
                    exit(-1);
                }
            }
            close(fd);
            return 0;
        }
        cout << endl;
    }
}
