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
    return myList.end(); // C++���� iterator�� null�� ���� �� ��� �̷��� ��ȯ.
}


int main() {
    list<Book> bookList;
    list<Book>::iterator it;

}