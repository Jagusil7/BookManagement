#include "stdafx.h"

int main()
{
	int input = 0;
	BookManager bm;

	string bookname;
	string writer;
	string number;
	for (int i = 0; i < 10; i++)
	{
		bookname = "book" + to_string(i);
		writer = "Writer" + to_string(i);
		number = to_string(i);
		bm.InsertBook(bookname, writer, number);
	}
	while (true)
	{
		cout << "대출은 1 반납은 2 종료는 0을 입력하세요" << endl;
		cin >> input;

		if (input == 0)
		{
			break;
		}
		else if (input == 1)
		{
			cout << "대여할 책 이름을 입력해 주세요 : ";
			cin >> bookname;
			Book* temp = bm.FindBook(bookname);
			// 찾는 책이 있을경우 상태를 확인합니다.
			if (temp != nullptr)
			{
				// 책이 도서관에 있을경우 대여합니다.
				if (temp->getStatus() == 0)
				{
					cout << bookname << "책을 대여합니다" << endl;
					temp->setStatus();
				}
				// 대여중일경우 불가능 메세지를 넘깁니다.
				else
				{
					cout << bookname << "책이 이미 대여중입니다" << endl;
				}
			}
			// 찾는 책이없을경우 출력합니다.
			else
			{
				cout << "찾는 책이 없습니다" << endl;
			}
		}
		else if (input == 2)
		{
			cout << "반납할 책 이름을 입력해 주세요 : ";
			cin >> bookname;
			Book* temp = bm.FindBook(bookname);
			// 책을 찾으면 반납가능한지 확인합니다.
			if (temp != nullptr)
			{
				//대여중이 아니면 불가능 메세지를 반환합니다.
				if (temp->getStatus() == 0)
				{
					cout << bookname << "책이 대여중이 아닙니다" << endl;
				}
				//대여중일경우 반납합니다.
				else
				{
					cout << bookname << "책을 반납합니다" << endl;
					temp->setStatus();
				}
			}
			//찾는책이 없을경우 출력합니다.
			else
			{
				cout << "찾는 책이 없습니다" << endl;
			}
		}
	}

	return 0;
}