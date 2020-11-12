#include "stdafx.h"
#include "BookManager.h"

BookManager::BookManager()
{
}

BookManager::~BookManager()
{
}

void BookManager::InsertBook(string name, string writer, string number)
{
	Book* insertBook =  new Book(name,writer,number);
	Book* tempBook = head;
	// 만약 head가 비어있으면 이 책이 첫 책이다.
	if (head == nullptr)
	{
		head = insertBook;
	}
	// 아닐경우에
	else
	{
		// 책의 맨끝까지 갑니다.
		while (tempBook->next != nullptr)
		{
			tempBook = tempBook->next;
		}
		// 맨끝에 새로운 책을 추가합니다.
		tempBook->next = insertBook;
	}

}
//원하는 책을 찾습니다.
Book* BookManager::FindBook(string name)
{
	Book* tempBook = head;
	// 이름이 같으면 반환합니다.
	if (tempBook->getTitle() == name)
	{
		cout << "책을 찾았습니다" << endl;
		return tempBook;
	}
	else
	{
		// 책 목록 전체를 확인합니다.
		while (tempBook->next != nullptr)
		{
			tempBook = tempBook->next;
			if (tempBook->getTitle() == name)
			{
				cout << "책을 찾았습니다" << endl;
				return tempBook;
			}
		}
		
	}
	//책을 찾지못하면 nullptr을 반환합니다.
	cout << "책을 찾지못했습니다" << endl;
	return nullptr;
}
