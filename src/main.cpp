#include <fcntl.h>
#include <iostream>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "BookInfo.hpp"

using namespace std;

// title로 도서 찾기 (완전 일치 기준)
list<Book>::iterator find_title_same(list<Book> &myList, string compare) {
    list<Book>::iterator it;
    for (it = myList.begin(); it != myList.end(); ++it) {
        if ((*it).getTitle() == compare) {
            return it;
        }
    }
    return myList.end();
    // C++에서 iterator는 null을 가질 수 없어서 이렇게 반환.
}
// title로 도서 찾기 (해당 문자열 포함 기준)
list<Book>::iterator find_title(list<Book> &myList, string compare) {
    list<Book>::iterator it;
    for (it = myList.begin(); it != myList.end(); ++it) {
        if ((*it).getTitle().find(compare) != string::npos)
            return it;
    }
    return myList.end();
}
list<Book>::iterator find_writer_same(list<Book> &myList, string compare) {
    list<Book>::iterator it;
    for (it = myList.begin(); it != myList.end(); ++it) {
        if ((*it).getWriter() == compare) {
            return it;
        }
    }
    return myList.end();
}
list<Book>::iterator find_writer(list<Book> &myList, string compare) {
    list<Book>::iterator it;
    for (it = myList.begin(); it != myList.end(); ++it) {
        if ((*it).getWriter().find(compare) != string::npos)
            return it;
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
            iter = find_title_same(bookList, title);
            if (iter == bookList.end()) {
                iter = find_title(bookList, title);
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
