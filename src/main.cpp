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
    return myList.end(); // C++에서 iterator는 null을 가질 수 없어서 이렇게 반환.
}


int main() {
    list<Book> bookList;
    list<Book>::iterator it;

}