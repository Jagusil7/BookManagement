#include "BookInfo.hpp"
#include <iostream>
#include <string.h>
#include <string>
#include <list>

using namespace std;

// title�� ���� ã�� (���� ��ġ ����)
list<Book>::iterator find_title_same(list<Book> &myList, string compare) {
    list<Book>::iterator it;
    for (it = myList.begin(); it != myList.end(); ++it) {
        if ((*it).getTitle() == compare) {
            return it;
        }
    }
    return myList.end();
    // C++���� iterator�� null�� ���� �� ��� �̷��� ��ȯ.
}
// title�� ���� ã�� (�ش� ���ڿ� ���� ����)
list<Book>::iterator find_title(list<Book>& myList, string compare) {
    list<Book>::iterator it;
    for (it = myList.begin(); it != myList.end(); ++it) {
        if ((*it).getTitle().find(compare) != string::npos)
            return it;
    }
    return myList.end();
}
list<Book>::iterator find_writer_same(list<Book>& myList, string compare) {
    list<Book>::iterator it;
    for (it = myList.begin(); it != myList.end(); ++it) {
        if ((*it).getWriter() == compare) {
            return it;
        }
    }
    return myList.end();
}
list<Book>::iterator find_writer(list<Book>& myList, string compare) {
    list<Book>::iterator it;
    for (it = myList.begin(); it != myList.end(); ++it) {
        if ((*it).getWriter().find(compare) != string::npos)
            return it;
    }
    return myList.end();
}

int main() {
    list<Book> bookList;
    list<Book>::iterator it;

    //* ���� �׽�Ʈ
    Book myBook("Title1", "Me1", "2");
    bookList.push_back(myBook);
    myBook = Book("Title2", "Me2", "2");
    bookList.push_back(myBook);
    myBook = Book("Title3", "Me3", "2");
    bookList.push_back(myBook);

    it = find_title_same(bookList, "Title1");
    if (it == bookList.end())
        cout << "ã�� ������ ����." << endl;
    else
        cout << "���� ����. ����: " + (*it).getWriter() << endl;

    it = find_title(bookList, "3");
    if (it == bookList.end())
        cout << "�ش� ���ڿ��� �� ���� ����." << endl;
    else
        cout << "�ش� ���ڿ��� �� ���� ����. ����: " + (*it).getWriter() << endl;

    return 0;
}