#include "BookInfo.hpp"
#include <iostream>
#include <string.h>
#include <string>
#include <list>

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

    //* 이하 테스트
    Book myBook("Title1", "Me1", "2");
    bookList.push_back(myBook);
    myBook = Book("Title2", "Me2", "2");
    bookList.push_back(myBook);
    myBook = Book("Title3", "Me3", "2");
    bookList.push_back(myBook);

    it = find_title_same(bookList, "Title1");
    if (it == bookList.end())
        cout << "찾는 도서가 없음." << endl;
    else
        cout << "도서 존재. 저자: " + (*it).getWriter() << endl;

    it = find_title(bookList, "3");
    if (it == bookList.end())
        cout << "해당 문자열이 들어간 도서 없음." << endl;
    else
        cout << "해당 문자열이 들어간 도서 존재. 저자: " + (*it).getWriter() << endl;

    return 0;
}