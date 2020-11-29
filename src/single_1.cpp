
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
#define MAX_NAME_LEN 64
#define MAX_ID_LEN 20
// 디버그 편의를 위해 단일 파일로 제작.
// 추후 완전히 완성 후 분리.

class Book {
  public:
    Book() {
        memset(this->title, 0x00, MAX_NAME_LEN + 1);
        memset(this->writer, 0x00, MAX_NAME_LEN + 1);
        memset(this->bookNum, 0x00, MAX_NAME_LEN + 1);
        memset(this->status, 0x00, MAX_NAME_LEN + 1);
    }
    Book(string title, string writer, string bookNum, string id = "") {
        memcpy(this->title, title.c_str(), MAX_NAME_LEN);
        memcpy(this->writer, writer.c_str(), MAX_NAME_LEN);
        memcpy(this->bookNum, bookNum.c_str(), MAX_NAME_LEN);
        memcpy(this->status, id.c_str(), MAX_NAME_LEN);
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
    // void setStatus(string want) {
    //    this->status = want; } // want = id?
    /*void setStatus(string want) {
        memcpy(this->status, want.c_str(), MAX_NAME_LEN);
    }*/
    void setStatus(string status) {
        memcpy(this->status, status.c_str(), MAX_NAME_LEN);
    }

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

// guest만 가입 가능/ 관리자는 main함수 처음에(id:manager123,
// password:ilovebook, personalNum:0)로 따로 만들어주세요!

class Login {
  public:
    Login() {
        memset(this->id, 0x00, MAX_NAME_LEN + 1);
        memset(this->password, 0x00, MAX_NAME_LEN + 1);
        this->personalNo = 0;
    }
    Login(string id, string password) {

        strcpy(this->id, id.c_str());
        strcpy(this->password, password.c_str());
        this->personalNo = 1; // guest 가입하면 자동적으로 1부터
        // personalnumber 부여(따로 넣어줄 필요 X)
    }

    void setId(string id) { memcpy(this->id, id.c_str(), MAX_NAME_LEN); }
    void setPassword(string password) {
        memcpy(this->password, password.c_str(), MAX_NAME_LEN);
    }
    void setPersonalNo(int personalNo) { this->personalNo = personalNo; }

    string getId() { return string(this->id); }
    string getPassword() { return string(this->password); }
    int getPersonalNo() { return this->personalNo; }

  private:
    char id[MAX_ID_LEN];
    char password[MAX_ID_LEN];
    int personalNo;
};

list<Login> Register(string id, string password) {

    list<Login> LoginList;
    Login login = Login(id, password);

    Login manager = Login("manager123", "ilovebook");
    manager.setPersonalNo(0);

    string filepath = "./member.dat";
    int fd = open(filepath.c_str(), O_CREAT | O_APPEND | O_WRONLY, 0644);
    if (fd == -1) {
        perror("open() error");
        exit(-1);
    }
    if (write(fd, &login, sizeof(Login)) == -1) {
        perror("write() error");
        exit(-1);
    }

    Login *buf = new Login();
    while (read(fd, buf, sizeof(Login)) != 0) {
        Login readlist(buf->getId(), buf->getPassword());
        LoginList.push_back(readlist);
    }

    close(fd);
    cout << "successfully registered" << endl;
    return LoginList;
}

//인자로 로그인 정보가 담겨있는 리스트,찾으려는 아이디와 패스워드가 들어감
//일치하는 아이디와 비밀번호가 있으면 manager:1, guest:2 반환/ 없으면 0 반환
int matchLogin(list<Login> &LoginList, string findid, string findpass) {
    list<Login>::iterator it;
    for (it = LoginList.begin(); it != LoginList.end(); ++it) {
        if (findid == it->getId()) {
            if (findpass == it->getPassword()) {
                if (it->getPersonalNo() == 0) {
                    return 1;
                } else {
                    return 2;
                }
            }
        }
    }
    return 0;
}

// 모드에 따라 이름/저자로 완전히 일치하는 도서 찾기
// mode: 0(제목), 기타(저자)
list<Book>::iterator findSame(list<Book> &myList, int mode, string compare) {
    list<Book>::iterator it;
    string temp;
    for (it = myList.begin(); it != myList.end(); ++it) {
        if (mode == 0)
            temp = it->getTitle();
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
list<Book>::iterator findContain(list<Book> &myList, int mode, string compare) {
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

// 출력 (반복되는 부분 정리)
void printStyle(list<Book>::iterator &iter) {
    cout << "TITLE:" << iter->getTitle() << " WRITER:" << iter->getWriter()
         << " BOOKNUM:" << iter->getBookNum()
         << " Rented ID:" << iter->getStatus() << endl;
}

// 해당 아이디로 빌린 도서 출력 (없으면 false)
bool printRent(list<Book> &myList, string id) {
    list<Book>::iterator it;
    bool result = false;

    for (it = myList.begin(); it != myList.end(); ++it) {
        if ((it->getStatus()).compare(id) == 0) {
            result = true;
            printStyle(it);
        }
    }
    return result;
}

int main() {
    //관리자는 main함수 처음에(id:manager123, password:ilovebook, personalNum:0)
    // Register("manager123", "ilovebook");

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
        Book book(buf->getTitle(), buf->getWriter(), buf->getBookNum(),
                  buf->getStatus());
        bookList.push_back(book);
    }

    string id = "";
    string password = "";

    int result; // manager, guest

    while (1) {

        cout << "<Login Page>" << endl
             << "[0] Register" << endl
             << "[1] Login" << endl
             << ">> ";
        int menu;
        cin >> menu;
        getchar();
        cout << endl;
        if (menu == 0) { // Register
            cout << "<REGISTER>" << endl;
            cout << "Enter ID: ";
             cin >> id;
             getchar();
             cout << "Enter Password: ";
             cin >> password;
             getchar();

             Login login = Login(id, password);

            string filepath = "./member.dat";
            int rfd =
                open(filepath.c_str(), O_CREAT | O_APPEND | O_WRONLY, 0644);
            if (rfd == -1) {
                perror("open() error");
                exit(-1);
            }

            if (write(rfd, &login, sizeof(Login)) == -1) {
                perror("write() error");
                exit(-1);
            }

            close(rfd);
            cout << "successfully registered" << endl;

            cout << endl;
        } else if (menu == 1) { // Login

            list<Login> loginList;
            list<Login>::iterator liter;

            int rfd = 0;
            string filepath = "./member.dat";
            Login *rbuf = (Login *)malloc(sizeof(Login));
            rfd = open(filepath.c_str(), O_RDONLY);
            if (rfd == -1) {
                perror("open() error!");
                exit(-1);
            }

            while (read(rfd, rbuf, sizeof(Login)) != 0) {
                Login member(rbuf->getId(), rbuf->getPassword());
                loginList.push_back(member);
            }
            close(rfd);

            for (liter = loginList.begin(); liter != loginList.end(); liter++) { //set manager personalNo to 0
                if (liter->getId() == "manager123" &&
                    liter->getPassword() == "ilovebook")
                    liter->setPersonalNo(0);
                cout << liter->getId() << " " << liter->getPassword() << " "
                     << liter->getPersonalNo() << endl;
            }

            cout << "<LOGIN>" << endl;
            cout << "Enter ID: ";
            cin >> id;
            getchar();
            cout << "Enter Password: ";
            cin >> password;
            getchar();
            result = matchLogin(loginList, id, password);
            if (result == 1 || result == 2) {
                break;
            } else {
                cout << "일치하는 아이디와 비밀번호가 존재하지 않습니다."
                     << endl;
            }
        }
    }

    // manager menu
    while (result == 1) {
        cout << "<MANAGER MENU>" << endl
             << "[0] Add Book" << endl
             << "[1] Delete Book" << endl
             << "[2] Book List" << endl
             << "[3] Search" << endl
             << "[4] Save and Exit" << endl
             << ">> ";
        int menu;
        cin >> menu;
        getchar();
        cout << endl;

        if (menu == 0) { // add book
            string title = "";
            string writer = "";
            string bookN = "";

            cout << "[ADD]" << endl << "Title: ";
            getline(cin, title);
            cout << "Writer: ";
            getline(cin, writer);
            cout << "BookNo: ";
            getline(cin, bookN);

            Book book(title, writer, bookN);
            bookList.push_back(book);

        } else if (menu == 1) { // delete book
            string del;
            cout << "[DELETE]" << endl << "Title: ";
            getline(cin, del);

            for (iter = bookList.begin(); iter != bookList.end(); iter++) {
                if (iter->getTitle() == del) {
                    bookList.erase(iter);
                    break;
                }
            }
            if (iter == bookList.end()) {
                cout << "ERROR: doesn't exist";
            }
        } else if (menu == 2) { // print book list
            cout << "[PRINT]" << endl;
            for (iter = bookList.begin(); iter != bookList.end(); ++iter) {
                printStyle(iter);
            }

        } else if (menu == 3) { // search book
            cout << "[SEARCH]" << endl;
            cout << "Find Title: ";
            string title;
            getline(cin, title);

            iter = findSame(bookList, 0, title);
            if (iter == bookList.end()) {
                iter = findContain(bookList, 0, title);
                if (iter == bookList.end())
                    cout << "찾는 도서가 없습니다." << endl;
                else {
                    cout << "해당 문자열이 들어간 도서가 존재합니다." << endl;
                    printStyle(iter);
                }
            } else {
                printStyle(iter);
            }
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
            break;
        }
    }

    // guest menu
    while (result == 2) {
        cout << "<Guest MENU>" << endl
             << "[0] Print List" << endl
             << "[1] Search" << endl
             << "[2] Rent" << endl
             << "[3] Print My Rented Book" << endl
             << "[4] Save and Exit" << endl
             << ">> ";
        int menu;
        cin >> menu;
        getchar();
        cout << endl;

        if (menu == 0) { // print book list
            cout << "[PRINT]" << endl;
            for (iter = bookList.begin(); iter != bookList.end(); ++iter) {
                printStyle(iter);
            }

        } else if (menu == 1) { // search book
            cout << "[SEARCH]" << endl;
            cout << "Find Title: ";
            string title;
            getline(cin, title);

            iter = findSame(bookList, 0, title);
            if (iter == bookList.end()) {
                iter = findContain(bookList, 0, title);
                if (iter == bookList.end())
                    cout << "찾는 도서가 없습니다." << endl;
                else {
                    cout << "해당 문자열이 들어가는 도서가 존재합니다." << endl;
                    printStyle(iter);
                }
            } else {
                printStyle(iter);
            }
        } else if (menu == 2) { // rent
            string title;

            cout << "[RENT]" << endl;
            cout << "Title: ";
            getline(cin, title);

            iter = findSame(bookList, 0, title);
            if (iter == bookList.end()) {
                cout << "없는 도서입니다." << endl << endl;
                continue;
            }
            if (iter->getStatus() != "") {
                cout << "이미 대여 중인 도서입니다." << endl << endl;
                continue;
            }
            iter->setStatus(id);
            cout << "빌렸습니다. (ID:" << id << ")" << endl;

        } else if (menu == 3) { // rented book

            cout << "[INQUIRY]" << endl;

            if (printRent(bookList, id) == false) {
                cout << "Nothing." << endl;
            }
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
            break;
        }
    }
    return 0;
}
