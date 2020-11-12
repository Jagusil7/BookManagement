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
             << "[3] Save and Exit" << endl
             << ">>";
        int menu;
        cin >> menu;
        cout << endl;
        if (menu == 0) {
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

        } else if (menu == 1) {
            string del;
            cout << "[DELETE]" << endl << "ID: ";
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
        } else if (menu == 3) { // save doc and exit
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
